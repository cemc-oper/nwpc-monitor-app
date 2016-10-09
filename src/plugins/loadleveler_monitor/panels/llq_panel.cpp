#include "llq_panel.h"
#include "ui_query_panel.h"

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
#include <QtCharts/QChart>
#include <QMessageBox>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Panels;
using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;
using namespace QtCharts;

LlqPanel::LlqPanel(QWidget *parent) :
    QueryPanel(parent)
{
    ui->argument_edit->setPlaceholderText(tr("use command llq's arguments, such as '-u nwp_qu', '-c serial' and so on."));
    setupTemplate();
    setupStyle();

    setupOperationAction();
}

LlqPanel::~LlqPanel()
{
}

void LlqPanel::slotRequestQuery()
{
    if(!hasSession())
    {
        QMessageBox::warning(this, tr("LoadLeveler Monitor"), tr("Please choose a session."));
        return;
    }
    QMap<QString, QString> args = getSessionArguments();
    args["command"] = "llq";
    QString arg_string = ui->argument_edit->text();
    if(!arg_string.isEmpty())
        args["command"] += " "+arg_string;

    LoadLevelerMonitorPlugin::client()->runLlqCommand(args, this);
}

void LlqPanel::slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response)
{
    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] start";    

    // request time
    setRequestTimeLable(command_response.request_date_time_);
    // response time
    QDateTime received_date_time = QDateTime::currentDateTime();
    setResponseSecondLabel(command_response.request_date_time_, received_date_time);

    // response json doc
    QJsonDocument doc = QJsonDocument::fromJson(command_response.std_out_.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlqPanel::slotReciveResponseStdOut] result is not a json string.";
        QDateTime response_handle_finish_time = QDateTime::currentDateTime();
        setResponseHandleSecondLabel(received_date_time, response_handle_finish_time);
        return;
    }

    QJsonObject content_object = doc.object();
    if( content_object.contains("error"))
    {
        QString error_message = content_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LlqPanel::slotReciveResponseStdOut] ERROR:"<<error_message;
        setQueryModel(nullptr);
        // TODO：repeat is evil
        QDateTime response_handle_finish_time = QDateTime::currentDateTime();
        setResponseHandleSecondLabel(received_date_time, response_handle_finish_time);
        return;
    }

    // query command
    QJsonObject data = content_object["data"].toObject();
    QJsonObject request_object = data["request"].toObject();
    setRequestCommandLabel(request_object);

    // clear styles
    setTableStyleVisibility(false);
    ui->table_style_page->clear();

    //TODO: clear chart
    setChartStyleVisibility(false);
    //ui->chart_view->setChart(nullptr);

    setTextStyleVisibility(false);
    ui->text_sytel_page->clear();

    // build model
    QueryModel *model = LlqCommandManager::buildQueryModelFromResponse(doc);
    setQueryModel(model);

    // text style
    QJsonObject response_object = data["response"].toObject();
    QJsonObject message = response_object["message"].toObject();
    QString output_message = message["output"].toString();
    updateTextStylePage(output_message);

    // table style
    if(!query_model_)
    {
        ui->action_text_style->activate(QAction::Trigger);
        QDateTime response_handle_finish_time = QDateTime::currentDateTime();
        setResponseHandleSecondLabel(received_date_time, response_handle_finish_time);
        return;
    }

    setTableStyleVisibility(true);
    ui->action_table_style->activate(QAction::Trigger);

    // chart style
    if(!query_model_->isEmpty())
    {
        updateChartStylePage();
    }

    QDateTime response_handle_finish_time = QDateTime::currentDateTime();
    setResponseHandleSecondLabel(received_date_time, response_handle_finish_time);
    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] end";
}

void LlqPanel::slotQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index)
{
    //qDebug()<<"[LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest]";
    if (!index.isValid()) {
        return;
    }
    QueryItem *cur_item = static_cast<QueryItem*>(query_model_->itemFromIndex(index));
    QueryCategory c = cur_item->category();

    QMenu *context_menu = new QMenu{};
    QAction *title_action = new QAction{c.display_name_ + ": " + cur_item->text()};
    context_menu->addAction(title_action);
    context_menu->addSeparator();

    // add actions acording to category
    if(query_model_->categoryList().containsId(Constant::Llq::Id))
    {
        int detail_col = query_model_->categoryList().indexFromId(Constant::Llq::Id);
        QAction *detail_action = new QAction{tr("详细信息")};
        context_menu->addAction(detail_action);
        connect(detail_action, &QAction::triggered,
                [=](bool){
            QModelIndex id_index = index.sibling(index.row(), detail_col);
            if(!index.isValid())
            {
                detail_action->deleteLater();
                return;
            }
            QStandardItem *id_item = query_model_->itemFromIndex(id_index);
            QString id = id_item->text();
            qDebug()<<"[LlqPanel::slotQueryModelContextMenuRequest] llq.id:"<<id;

            QMap<QString, QString> args = getSessionArguments();
            args["command"] = "llq -l "+id;

            //TODO: 创建一个弹出窗口，接收命令执行结果，将窗口传递给 client。
            ClientCommandWidget *command_widget = new ClientCommandWidget();
            command_widget->show();

            LoadLevelerMonitorPlugin::client()->runCommand(args, command_widget);
            detail_action->deleteLater();
        });
    }

    if(query_model_->categoryList().containsId(Constant::Llq::Owner))
    {
        int owner_col = query_model_->categoryList().indexFromId(Constant::Llq::Owner);
        QModelIndex owner_index = index.sibling(index.row(), owner_col);
        QStandardItem *owner_item = query_model_->itemFromIndex(owner_index);
        QString owner = owner_item->text();

        QAction *owner_action = new QAction{tr("Query user ") + owner + tr("'s all jobs.")};
        context_menu->addAction(owner_action);
        connect(owner_action, &QAction::triggered,
                [=](bool){
            qDebug()<<"[LlqPanel::slotQueryModelContextMenuRequest] llq.owner:"<<owner;
            ui->argument_edit->setText("-u " + owner);
            slotRequestQuery();
            owner_action->deleteLater();
        });
    }

    if(query_model_->categoryList().containsId(Constant::Llq::Class))
    {
        int class_col = query_model_->categoryList().indexFromId(Constant::Llq::Class);
        QModelIndex class_index = index.sibling(index.row(), class_col);
        QStandardItem *class_item = query_model_->itemFromIndex(class_index);
        QString job_class = class_item->text();

        QAction *class_action = new QAction{tr("Query class ") + job_class + tr("'s all jobs.")};
        context_menu->addAction(class_action);
        connect(class_action, &QAction::triggered,
                [=](bool){
            qDebug()<<"[LlqPanel::slotQueryModelContextMenuRequest] llq.class:"<<job_class;
            ui->argument_edit->setText("-c " + job_class);
            slotRequestQuery();
            class_action->deleteLater();
        });
    }

    // show menu
    context_menu->exec(global_point);
    // delete objects
    delete context_menu;
    delete title_action;
}

void LlqPanel::setupTemplate()
{
    qDebug()<<"[LlqPanel::setupTemplate]";

    // template action
    //      text: 显示的文本
    //      data: llq的参数，例如 -l/-u nwp 等

    // template action
    template_action_list_.clear();
    template_action_list_.append(ui->action_default_template);
    ui->action_default_template->setData("");
    template_action_list_.append(ui->action_detail_template);
    ui->action_detail_template->setData("-l");
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
    ui->detail_template_button->setDefaultAction(ui->action_detail_template);
    ui->more_template_button->setDefaultAction(ui->action_more_template);

    // default state
    ui->action_default_template->setChecked(true);
}

void LlqPanel::setupStyle()
{
    qDebug()<<"[LlqPanel::setupStyle]";
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

    connect(ui->table_style_page, &TableStylePage::signalQueryModelContextMenuRequest,
            this, &LlqPanel::slotQueryModelContextMenuRequest);
}

void LlqPanel::setupOperationAction()
{
    cancel_action_ = new QAction{"llcancel"};
    cancel_action_->setObjectName("LlqPanel.OperationAction.cancel");
    connect(cancel_action_, &QAction::triggered, [=](bool){
        QMessageBox::StandardButton button = QMessageBox::warning(
                    this, tr("Warning"),
                    tr("llcancel is a dangrous command. Do you want to continue?"),
                    QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
            cancelSelectedJobs();
    });

    release_action_ = new QAction{"llhold_r"};
    release_action_->setObjectName("LlqPanel.OperationAction.release");
    connect(release_action_, &QAction::triggered, [=](bool){
        QMessageBox::StandardButton button = QMessageBox::warning(
                    this, tr("Warning"),
                    tr("llhold is a dangrous command. Do you want to continue?"),
                    QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
            releaseSelectedJobs();

    });

    QVector<QPointer<QAction>> action_vector;
    action_vector.push_back(cancel_action_);
    action_vector.push_back(release_action_);
    ui->table_style_page->setOperationButtons(action_vector);
}

void LlqPanel::cancelSelectedJobs()
{
    QList<int> checked_rows = Util::ModelView::getCheckedRows(query_model_);
    QStringList job_id_list = LlqPanel::getLlqJobIdList(query_model_, checked_rows);
    foreach(QString job_id, job_id_list)
    {
        QMap<QString, QString> args = getSessionArguments();
        args["command"] = "llcancel " + job_id;
        LoadLevelerMonitorPlugin::client()->runLlcancelCommand(args, this);
    }
}

void LlqPanel::releaseSelectedJobs()
{
    QList<int> checked_rows = Util::ModelView::getCheckedRows(query_model_);
    QStringList job_id_list = LlqPanel::getLlqJobIdList(query_model_, checked_rows);
    foreach(QString job_id, job_id_list)
    {
        QMap<QString, QString> args = getSessionArguments();
        args["command"] = "llhold -r " + job_id;
        LoadLevelerMonitorPlugin::client()->runLlholdCommand(args, this);
    }
}

void LlqPanel::updateChartStylePage()
{
    qDebug()<<"[LlqPanel::updateChartStylePage] chart style start";

    // clean chart type layout
    ui->chart_style_page->clear();

    // delete chart type actions
    QMapIterator<QAction *, LoadLevelerMonitor::Chart::ModelProcessor*> it(chart_type_action_map_);
    while (it.hasNext()) {
        it.next();
        QAction *action = it.key();
        chart_type_action_group_->removeAction(action);
        chart_type_action_map_.remove(action);
        action->deleteLater();
    }

    // create chart type action
    QSet<ProcessorCondition*> condition_set = LlqCommandManager::processorConditionList();
    QMultiMap<ProcessorCondition*, ModelProcessor*> processor_map = LlqCommandManager::processorMap();
    foreach(ProcessorCondition* condition, condition_set)
    {
        if(!condition->isMatch(query_model_))
            continue;
        QList<ModelProcessor*> processors = processor_map.values(condition);
        for (int i = 0; i < processors.size(); ++i)
        {
            ModelProcessor* processor = processors[i];
            QAction *action = new QAction{processor->displayName() ,this};
            action->setCheckable(true);
            action->setChecked(Qt::Unchecked);
            chart_type_action_map_[action] = processor;
            chart_type_action_group_->addAction(action);

            connect(action, &QAction::triggered, [=](bool flag){
                if(flag)
                {
                    showChart(action);
                }
            });
        }
    }

    // add action to layout
    ui->chart_style_page->setChartTypeActionGroup(chart_type_action_group_);

    // check if show chart style
    if(chart_type_action_map_.count() > 0 )
    {
        setChartStyleVisibility(true);
        chart_type_action_map_.keys().first()->activate(QAction::Trigger);
    }

    qDebug()<<"[LlqPanel::updateChartStylePage] chart style end";
}

QStringList LlqPanel::getLlqJobIdList(QueryModel *model, const QList<int> &row_list)
{
    QStringList job_id_list;
    int id_category_index = model->categoryList().indexFromId(Constant::Llq::Id);
    if(id_category_index == -1)
    {
        qWarning()<<"[LlqPanel::getLlqJobIdList] can't get id category";
        return job_id_list;
    }
    foreach(int row_index, row_list)
    {
        QStandardItem *id_item = model->invisibleRootItem()->child(row_index, id_category_index);
        if(id_item == nullptr)
        {
            qWarning()<<"[LlqPanel::getLlqJobIdList] can't get id in row:"<<row_index;
            continue;
        }
        job_id_list.append(id_item->text());
    }

    return job_id_list;
}
