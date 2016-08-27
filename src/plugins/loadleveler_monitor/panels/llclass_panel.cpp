#include "llclass_panel.h"
#include "ui_query_panel.h"
#include "../model/query_model.h"
#include "../model/llclass_command_manager.h"
#include "../loadleveler_monitor_widget.h"
#include "../loadleveler_monitor_plugin.h"
#include "../loadleveler_client.h"

using namespace LoadLevelerMonitor::Panels;
using namespace LoadLevelerMonitor::Model;

LlclassPanel::LlclassPanel(QWidget *parent) :
    QueryPanel(parent)
{
    setupTemplate();
    setupStyle();
}

LlclassPanel::~LlclassPanel()
{

}

void LlclassPanel::slotRequestQuery()
{
    QMap<QString, QString> args = monitor_widget_->getSessionArguments();
    args["command"] = "llclass";
    QString arg_string = ui->argument_edit->text();
    if(!arg_string.isEmpty())
        args["command"] += " "+arg_string;

    LoadLevelerMonitorPlugin::client()->runLlclassCommand(args, this);
}

void LlclassPanel::slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response)
{
    qDebug()<<"[LlclassPanel::slotReciveResponseStdOut] start";

    // run time
    QDateTime finish_date_time = QDateTime::currentDateTime();
    setRequestTimeLabel(command_response.request_date_time_, finish_date_time);

    // response json doc
    QJsonDocument doc = QJsonDocument::fromJson(command_response.std_out_.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlclassPanel::slotReciveResponseStdOut] result is not a json string.";
        return;
    }

    QJsonObject content_object = doc.object();
    if( content_object.contains("error"))
    {
        QString error_message = content_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LlclassPanel::slotReciveResponseStdOut] ERROR:"<<error_message;
        setQueryModel(nullptr);
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
    QueryModel *model = LlclassCommandManager::buildQueryModelFromResponse(doc);
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
        return;
    }

    setTableStyleVisibility(true);
    ui->action_table_style->activate(QAction::Trigger);

    // chart style
    if(!query_model_->isEmpty())
    {
        updateChartStylePage();
    }

    qDebug()<<"[LlqPanel::slotReciveResponseStdOut] end";
}

void LlclassPanel::slotQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index)
{

}

void LlclassPanel::setupTemplate()
{

}

void LlclassPanel::setupStyle()
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

    connect(style_action_group_, &QActionGroup::triggered, this, &LlclassPanel::slotStyleActionTriggered);

    ui->action_table_style->activate(QAction::Trigger);

    // style button
    ui->table_style_button->setDefaultAction(ui->action_table_style);
    ui->chart_style_button->setDefaultAction(ui->action_chart_style);
    ui->text_style_button->setDefaultAction(ui->action_text_style);

    connect(ui->table_style_page, &TableStylePage::signalQueryModelContextMenuRequest,
            this, &LlclassPanel::slotQueryModelContextMenuRequest);
}

void LlclassPanel::updateChartStylePage()
{

}
