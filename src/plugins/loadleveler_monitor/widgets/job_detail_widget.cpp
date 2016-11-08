#include "job_detail_widget.h"
#include "ui_job_detail_widget.h"

#include "../model/model_constants.h"
#include "../model/query_category.h"
#include "../model/query_item.h"
#include "../loadleveler_client.h"
#include "../loadleveler_monitor_plugin.h"
#include "file_viewer_widget.h"

#include <QStandardItemModel>
#include <QActionGroup>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QScopedPointer>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Widgets;
using namespace LoadLevelerMonitor::Model;
using namespace std;

JobDetailWidget::JobDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JobDetailWidget),
    style_action_group_{new QActionGroup{this}},
    property_model_{new QStandardItemModel{this}}
{
    ui->setupUi(this);
    ui->tree_view->setModel(property_model_);

    connect(ui->tree_view, &QTreeView::customContextMenuRequested,
            [=](const QPoint &pos){
        slotPropertyModelContextMenuRequest(ui->tree_view->mapToGlobal(pos), ui->tree_view->indexAt(pos));
    });
    setupStyle();
}

JobDetailWidget::~JobDetailWidget()
{
    delete ui;
}

void JobDetailWidget::setSession(const Core::SessionSystem::Session &session)
{
    session_ = session;
}

void JobDetailWidget::setJobId(const QString &job_id)
{
    ui->job_id_line_edit->setText(job_id);
}

void JobDetailWidget::receiveResponse(const QString &response)
{
    setResponseStylePage(response);

    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[JobDetailWidget::receiveResponse] result is not a json string.";
        return;
    }

    QJsonObject result_object = doc.object();

//    QString error_message = result_object["data"].toObject()["response"].toObject()["message"].toObject()["error_output"].toString();
//    setErrorOutputText(error_message);

    QString output_message = result_object["data"].toObject()["response"].toObject()["message"].toObject()["output"].toString();
    setOutputStylePage(output_message);

    setTreeStylePage(output_message);
}

void JobDetailWidget::slotStyleActionTriggered(QAction *action)
{
    int index = style_action_list_.indexOf(action);
    if(index != -1)
        ui->stacked_widget->setCurrentIndex(index);
    else
    {
        qWarning()<<"[JobDetailWidget::slotStyleActionTriggered] action don't find in action list:"<<action;
    }
}

void JobDetailWidget::slotPropertyModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    QStandardItem *cur_item = property_model_->itemFromIndex(index);
    qDebug()<<index.row()<<index.column()<<cur_item->parent();
    if(cur_item->parent()==nullptr)
        return;

    QStandardItem* property_name_item = property_model_->itemFromIndex(index.sibling(index.row(), 0));
    QStandardItem* value_item = property_model_->itemFromIndex(index.sibling(index.row(), 1));

    QString property_name = property_name_item->text();
    QString value = value_item->text();

    if(property_name == "Output File" || property_name == "Error Output File" || property_name == "Job Script")
    {
        QScopedPointer<QMenu> context_menu{new QMenu};
        QScopedPointer<QAction> see_action{new QAction{"See file..."}};
        context_menu->addAction(see_action.data());
        connect(see_action.data(), &QAction::triggered,
                [=](bool){
            requestSeeFile(value);
        });
        context_menu->exec(global_point);
    }
}

void JobDetailWidget::setupStyle()
{
    style_action_list_.append(ui->action_output_style);
    style_action_list_.append(ui->action_tree_style);
    style_action_list_.append(ui->action_response_style);

    foreach(QAction* action, style_action_list_)
    {
        style_action_group_->addAction(action);
    }

    connect(style_action_group_, &QActionGroup::triggered, this, &JobDetailWidget::slotStyleActionTriggered);

    ui->action_output_style->activate(QAction::Trigger);

    // style button
    ui->output_style_button->setDefaultAction(ui->action_output_style);
    ui->tree_style_button->setDefaultAction(ui->action_tree_style);
    ui->response_style_button->setDefaultAction(ui->action_response_style);
}

void JobDetailWidget::setResponseStylePage(const QString &response)
{
    ui->response_text_browser->setText(response);
}

void JobDetailWidget::setOutputStylePage(const QString &output)
{
    ui->output_text_browser->setText(output);
}

void JobDetailWidget::setTreeStylePage(const QString &output)
{
    property_model_->clear();
    property_map_.clear();

    QStringList record = output.split('\n');
    QString step_type = JobDetailWidget::getTextByLabel("Step Type", record);
    property_map_["Step Type"] = step_type;

    // job script
    QString job_script;
    if(step_type == "Serial")
    {
        job_script = JobDetailWidget::getTextByLabel("Cmd", record);
    }
    else if(step_type == "General Parallel")
    {
        job_script = JobDetailWidget::getTextByLabel("Executable", record);
    }
    else
    {
        qWarning()<<"[JobDetailWidget::setTreeStylePage] unsupported step type:"<< step_type;
    }
    property_map_["Job Script"] = job_script;

    QString output_script_path = JobDetailWidget::getTextByLabel("Out", record);
    property_map_["Out"] = output_script_path;
    QString error_script_path = JobDetailWidget::getTextByLabel("Err", record);
    property_map_["Err"] = error_script_path;
    QString initial_working_dir = JobDetailWidget::getTextByLabel("Initial Working Dir", record);
    property_map_["Initial Working Dir"] = initial_working_dir;

    QStandardItem *general_section = new QStandardItem{"General"};
    general_section->appendRow(
        QList<QStandardItem*>()<< new QStandardItem{"Step Type"} << new QStandardItem{ step_type }
    );
    general_section->appendRow(
        QList<QStandardItem*>()<< new QStandardItem{"Job Script"} << new QStandardItem{ job_script }
    );
    general_section->appendRow(
        QList<QStandardItem*>()<< new QStandardItem{"Output File"} << new QStandardItem{ output_script_path }
    );
    general_section->appendRow(
        QList<QStandardItem*>()<< new QStandardItem{"Error Ouput File"} << new QStandardItem{ error_script_path }
    );
    general_section->appendRow(
        QList<QStandardItem*>()<< new QStandardItem{"Initial Working Dir"} << new QStandardItem{ initial_working_dir }
    );

    property_model_->invisibleRootItem()->appendRow(general_section);
    property_model_->setColumnCount(2);
    property_model_->setHorizontalHeaderLabels(QStringList{"Property", "Value"});
    ui->tree_view->expandAll();
    ui->tree_view->setColumnWidth(0, 200);

    return;
}

void JobDetailWidget::requestSeeFile(const QString &file_path)
{
    QString path = file_path;
    QMap<QString, QString> args = session_.toArguments();
    if(!path.startsWith('/')){
        path = property_map_["Initial Working Dir"].toString() + "/" + path;
    }
    args["file"] = path;

    FileViewerWidget *widget = new FileViewerWidget();
    widget->show();
    LoadLevelerMonitorPlugin::client()->runFileCommand(args, widget);
}

QString JobDetailWidget::getTextByLabel(const QString &label, const QStringList &record)
{
    DefaultQueryCategoryType param = make_tuple(
                label,
                label,
                label,
                QueryValueType::String,
                "",
                kDetailLabelParser,
                QVariantList{label}
    );
    QueryCategory category = QueryCategoryFactory::createCateogry(param);
    QueryItem *item = QueryItem::buildDetailQueryItem(category, record);
    QString text = item->text();
    delete item;
    return text;
}
