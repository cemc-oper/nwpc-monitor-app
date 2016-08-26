#include "llq_panel.h"
#include "ui_llq_panel.h"

#include "../model/query_model.h"
#include "../model/query_item.h"
#include "../model/llq_command_manager.h"

#include "../chart/category_model_processor.h"
#include "../model/query_category_list.h"

#include "../loadleveler_monitor_plugin.h"
#include "../loadleveler_client.h"

#include "../client_command_widget.h"
#include "../loadleveler_monitor_widget.h"

#include <util/model_view_util.h>

#include <QActionGroup>
#include <QMap>
#include <QMenu>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>
#include <QtCharts>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Panels;
using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;
using namespace QtCharts;

LlqPanel::LlqPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LlqPanel),
    style_action_group_{new QActionGroup{this}},
    template_action_group_{new QActionGroup{this}}
{
    ui->setupUi(this);

    ui->query_command_frame->hide();
    ui->query_time_frame->hide();

    connect(ui->check_all_button, &QPushButton::clicked,
            [=](){
                Util::ModelView::changeAllItemsCheckState(query_model_, Qt::Checked);
            }
    );

    connect(ui->uncheck_all_button, &QPushButton::clicked,
            [=](){
                Util::ModelView::changeAllItemsCheckState(query_model_, Qt::Unchecked);
            }
    );

    connect(ui->query_button, &QPushButton::clicked,
            this, &LlqPanel::slotRequestQuery);

    connect(ui->argument_edit, &QLineEdit::returnPressed,
            this, &LlqPanel::slotRequestQuery);

    setupTemplate();
    setupStyle();
}

LlqPanel::~LlqPanel()
{
    delete ui;
    if(query_model_){
        query_model_->deleteLater();
    }
}

void LlqPanel::setMonitorWidget(LoadLevelerMonitorWidget *widget)
{
    monitor_widget_ = widget;
}

void LlqPanel::slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response)
{
    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] start";    

    QDateTime finish_date_time = QDateTime::currentDateTime();
    setCommandTime(command_response.request_date_time_, finish_date_time);

    QJsonDocument doc = QJsonDocument::fromJson(command_response.std_out_.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlqPanel::slotReciveResponseStdOut] result is not a json string.";
        return;
    }

    QJsonObject content_object = doc.object();
    if( content_object.contains("error"))
    {
        QString error_message = content_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LlqPanel::slotReciveResponseStdOut] ERROR:"<<error_message;
        setQueryModel(nullptr);
        return;
    }

    QString app = content_object["app"].toString();
    QString type = content_object["type"].toString();
    QJsonObject data = content_object["data"].toObject();

    QJsonObject request_object = data["request"].toObject();
    QString command = request_object["command"].toString();
    QJsonArray arguments = request_object["arguments"].toArray();
    QStringList arg_list;
    foreach(QJsonValue an_argument, arguments)
    {
        arg_list.append(an_argument.toString());
    }
    ui->query_command_label->setText(command + " " + arg_list.join(" "));
    ui->query_command_frame->show();

    // clear styles
    setTableStyleVisibility(false);
    ui->table_view->setModel(nullptr);

    setChartStyleVisibility(false);
    //TODO: clear chart
    //ui->chart_view->setChart(nullptr);

    setTextStyleVisibility(false);
    ui->text_view->clear();

    // build model
    QueryModel *model = LlqCommandManager::buildQueryModelFromResponse(doc);
    setQueryModel(model);

    // text style
    setTextStyleVisibility(true);
    QJsonObject response_object = data["response"].toObject();
    QJsonObject message = response_object["message"].toObject();
    QString output_message = message["output"].toString();
    updateTextStylePage(output_message);

    // table style
    if(!model)
    {
        ui->action_text_style->activate(QAction::Trigger);
        return;
    }

    setTableStyleVisibility(true);
    ui->action_table_style->activate(QAction::Trigger);

    // chart style
    if(model->isEmpty())
    {
        return;
    }
    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] chart style start";
    setChartStyleVisibility(true);

    CategoryModelProcessor *data_processor = LlqCommandManager::modelDataProcessor();
    data_processor->setQueryModel(model);
    QueryCategory c;
    switch(model->queryType())
    {
    case QueryType::LlqDefaultQuery:
        c = model->categoryList().categoryFromId("owner");
        break;
    case QueryType::LlqDetailQuery:
        c = model->categoryList().categoryFromId("owner");
    }
    if(!c.isValid())
    {
        qWarning()<<"[LlqPanel::slotReciveResponseStdOut] chart category is not valid";
        return;
    }
    data_processor->setQueryModel(model);
    QueryCategoryList category_list;
    category_list.append(c);
    data_processor->setQueryCategoryList(category_list);

    QChart *query_chart = data_processor->generateChart();
    if(!query_chart)
    {
        qWarning()<<"[LlqPanel::slotReciveResponseStdOut] chart is null";
        return;
    }
    QChart *old_chart = ui->chart_view->chart();
    if(old_chart)
        old_chart->deleteLater();
    ui->chart_view->setChart(query_chart);

    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] chart style end";

    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] end";
}

void LlqPanel::slotStyleActionTriggered(QAction *action)
{
    int index = style_action_list_.indexOf(action);
    if(index != -1)
        ui->view_area_stacked_widget->setCurrentIndex(index);
    else
    {
        qWarning()<<"[LlqPanel::slotStyleActionTriggered] action don't find in action list:"<<action;
    }
}

void LlqPanel::slotTemplateActionTriggered(QAction *action)
{
    int index = template_action_list_.indexOf(action);
    if(index != -1)
    {
        ui->argument_edit->setText(action->data().toString());
    }
    else
    {
        qWarning()<<"[LlqPanel::slotTemplateActionTriggered] action don't find in action list:"<<action;
    }
}

void LlqPanel::slotRequestQuery()
{
    QMap<QString, QString> args = monitor_widget_->getSessionArguments();
    args["command"] = "llq";
    QString arg_string = ui->argument_edit->text();
    if(!arg_string.isEmpty())
        args["command"] += " "+arg_string;

    LoadLevelerMonitorPlugin::client()->runLlqCommand(args, this);
}

void LlqPanel::slotQueryRecordContextMenuRequest(const QPoint &pos)
{
    //qDebug()<<"[LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest]";
    QModelIndex index = ui->table_view->indexAt(pos);
    if (index.isValid()) {
        QueryItem *cur_item = static_cast<QueryItem*>(query_model_->itemFromIndex(index));
        QueryCategory c = cur_item->category();

        QMenu *context_menu = new QMenu{};
        QAction *title_action = new QAction{c.display_name_ + ": " + cur_item->text()};
        context_menu->addAction(title_action);
        context_menu->addSeparator();

        // add actions acording to category
        QAction *detail_action = new QAction{tr("详情")};
        context_menu->addAction(detail_action);

        // show menu
        QAction *action = context_menu->exec(ui->table_view->mapToGlobal(pos));
        if(action == detail_action)
        {
            QModelIndex id_index = index.sibling(index.row(), 1);
            if(index.isValid())
            {
                QStandardItem *id_item = query_model_->itemFromIndex(id_index);
                QString id = id_item->text();
                qDebug()<<"[LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest]"<<id;
                QMap<QString, QString> args = monitor_widget_->getSessionArguments();
                args["command"] = "llq -l "+id;

                //TODO: 创建一个弹出窗口，接收命令执行结果，将窗口传递给 client。
                ClientCommandWidget *command_widget = new ClientCommandWidget();

//                command_widget->runPythonCommand(args);
                command_widget->show();

                LoadLevelerMonitorPlugin::client()->runCommand(args, command_widget);
            }
        }
        delete context_menu;
        delete title_action;
        delete detail_action;
    }
}

void LlqPanel::setupTemplate()
{
    // template action
    //      text: 显示的文本
    //      data: llq的参数，例如 -l/-u nwp 等

    // template action
    template_action_list_.clear();
    template_action_list_.append(ui->action_default_template);
    ui->action_default_template->setData("");
    template_action_list_.append(ui->action_llqn_template);
    ui->action_llqn_template->setData("-l");
    template_action_list_.append(ui->action_more_template);
    ui->action_more_template->setData("");

    // tempalte action group
    foreach(QAction *action, template_action_list_)
    {
        template_action_group_->addAction(action);
    }
    connect(template_action_group_, &QActionGroup::triggered, this, &LlqPanel::slotTemplateActionTriggered);

    // more template action
    QMenu *more_template_menu = new QMenu{this};
    QAction *action = nullptr;
    action = new QAction(tr("llq -u nwp"));
    action->setData("-u nwp");
    more_template_menu->addAction(action);
    action = new QAction(tr("llq -u nwp_qu"));
    action->setData("-u nwp_qu");
    more_template_menu->addAction(action);

    connect(more_template_menu, &QMenu::triggered, [=](QAction *a){
        ui->action_more_template->setText(a->text());
        ui->action_more_template->setData(a->data());
        ui->action_more_template->activate(QAction::Trigger);
    });
    ui->action_more_template->setMenu(more_template_menu);

    // template tool button
    ui->default_template_button->setDefaultAction(ui->action_default_template);
    ui->llqn_template_button->setDefaultAction(ui->action_llqn_template);
    ui->more_template_button->setDefaultAction(ui->action_more_template);

    // default state
    ui->action_default_template->setChecked(true);
}

void LlqPanel::setupStyle()
{
    // style action
    style_action_list_.clear();
    style_action_list_.append(ui->action_table_style);
    style_action_list_.append(ui->action_chart_style);
    style_action_list_.append(ui->action_text_style);

    foreach(QAction *action, style_action_list_)
    {
        style_action_group_->addAction(action);
    }

    connect(style_action_group_, &QActionGroup::triggered, this, &LlqPanel::slotStyleActionTriggered);

    ui->action_table_style->activate(QAction::Trigger);

    // style button
    ui->table_style_button->setDefaultAction(ui->action_table_style);
    ui->chart_style_button->setDefaultAction(ui->action_chart_style);
    ui->text_style_button->setDefaultAction(ui->action_text_style);
}

void LlqPanel::setTableStyleVisibility(bool is_visible)
{
    ui->table_style_button->setHidden(!is_visible);
}

void LlqPanel::setChartStyleVisibility(bool is_visible)
{
    ui->chart_style_button->setHidden(!is_visible);
}

void LlqPanel::setTextStyleVisibility(bool is_visible)
{
    ui->text_style_button->setHidden(!is_visible);
}

void LlqPanel::setQueryModel(QPointer<QueryModel> query_model)
{
    if(query_model_)
    {
        ui->table_view->setModel(0);
        query_model_->deleteLater();
    }
    query_model_ = query_model;

    ui->table_view->setModel(query_model_);
    ui->table_view->horizontalHeader()->setStretchLastSection(true);

    if(!query_model_)
    {
        return;
    }

    switch(query_model_->queryType())
    {
    case QueryType::LlqDefaultQuery:
        ui->table_view->setColumnWidth(1, 200); // id
        ui->table_view->setColumnWidth(3, 150); //
        break;
    case QueryType::LlqDetailQuery:
        // TODO: 目前无法保留调整过的列宽，每次都恢复到初始状态
        ui->table_view->setColumnWidth(1, 160); // id
        ui->table_view->setColumnWidth(2, 80);
        ui->table_view->setColumnWidth(4, 400);
        break;
    default:
        break;
    }

    ui->table_view->sortByColumn(0, Qt::AscendingOrder);

    disconnect(ui->table_view, &QTableView::customContextMenuRequested, 0, 0);
    ui->table_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table_view, &QTableView::customContextMenuRequested,
            this, &LlqPanel::slotQueryRecordContextMenuRequest);
}

void LlqPanel::setCommandTime(const QDateTime &request_time, const QDateTime &finish_time)
{
    qint64 interval_seconds = request_time.msecsTo(finish_time);
    ui->query_time_label->setText(QString::number(interval_seconds/1000.0) + " seconds");
    ui->query_time_frame->show();
}

void LlqPanel::updateTextStylePage(const QString &str)
{
    ui->text_view->setText(str);
}
