#include "loadleveler_client.h"
#include "loadleveler_monitor_plugin.h"
#include "client_command_widget.h"
#include "panels/llq_panel.h"
#include "panels/llclass_panel.h"
#include "widgets/job_detail_widget.h"

#include <python_env_plugin/python_command.h>
#include <core_plugin/progress_system/progress_manager.h>
#include <core_plugin/progress_system/progress_item_widget.h>

#include <QProcess>
#include <QDateTime>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace PythonEnv;
using namespace Core::ProgressSystem;

LoadLevelerClient::LoadLevelerClient(QObject *parent):
    PythonEngine(parent)
{

}

LoadLevelerClient::~LoadLevelerClient()
{

}

void LoadLevelerClient::runLlqCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel)
{
    qDebug()<<"[LoadLevelerClient::runLlqCommand] start";
    QDateTime request_date_time = QDateTime::currentDateTime();
    QStringList arguments;
    PythonCommand* command = createPythonCommand();

    if(!llq_panel.isNull())
    {
        connect(command, &PythonCommand::signalFinished,
                llq_panel, &Panels::LlqPanel::slotReciveCommandResponse);
    }

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<"[LoadLevelerClient::runLlqCommand] args:"<<arguments;

    QFuture<void> future = executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    ProgressItemWidget *progress_item_widget =  ProgressManager::addTask(future, args["command"]);
    progress_item_widget->setDescription("Run shell command: " + args["command"] + " ...");

    qDebug()<<"[LoadLevelerClient::runLlqCommand] end";
}

// TODO: repeat is evil
void LoadLevelerClient::runLlcancelCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel)
{
    qDebug()<<"[LoadLevelerClient::runLlcancelCommand] start";
    QDateTime request_date_time = QDateTime::currentDateTime();
    QStringList arguments;
    PythonCommand* command = createPythonCommand();

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<"[LoadLevelerClient::runLlcancelCommand] args:"<<arguments;

    QFuture<void> future = executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    ProgressItemWidget *progress_item_widget =  ProgressManager::addTask(future, args["command"]);
    progress_item_widget->setDescription("Run shell command: " + args["command"] + " ...");

    qDebug()<<"[LoadLevelerClient::runLlcancelCommand] end";
}

void LoadLevelerClient::runLlholdCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel)
{
    qDebug()<<"[LoadLevelerClient::runLlcancelCommand] start";
    QDateTime request_date_time = QDateTime::currentDateTime();
    QStringList arguments;
    PythonCommand* command = createPythonCommand();

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<"[LoadLevelerClient::runLlholdCommand] args:"<<arguments;

    QFuture<void> future = executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    ProgressItemWidget *progress_item_widget =  ProgressManager::addTask(future, args["command"]);
    progress_item_widget->setDescription("Run shell command: " + args["command"] + " ...");

    qDebug()<<"[LoadLevelerClient::runLlholdCommand] end";
}

void LoadLevelerClient::runLlclassCommand(QMap<QString, QString> args, QPointer<Panels::QueryPanel> query_panel)
{
    qDebug()<<"[LoadLevelerClient::runLlqCommand] start";
    QDateTime request_date_time = QDateTime::currentDateTime();
    QStringList arguments;
    PythonCommand* command = createPythonCommand();

    if(!query_panel.isNull())
    {
        connect(command, &PythonCommand::signalFinished,
                query_panel, &Panels::QueryPanel::slotReciveCommandResponse);
    }

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];
    qDebug()<<"[LoadLevelerClient::runLlclassCommand] args:"<<arguments;

    QFuture<void> future = executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );
    ProgressItemWidget *progress_item_widget =  ProgressManager::addTask(future, args["command"]);
    progress_item_widget->setDescription("Run shell command: " + args["command"] + " ...");

    qDebug()<<"[LoadLevelerClient::runLlclassCommand] end";
}

void LoadLevelerClient::runCommand(QMap<QString, QString> args, QPointer<ClientCommandWidget> command_widget)
{
    qDebug()<<"[LoadLevelerClient::runCommand] start";
    QStringList arguments;
    PythonCommand* command = createPythonCommand();

    if(!command_widget.isNull())
    {
        connect(command, &PythonCommand::signalStdOutString,
                command_widget, &ClientCommandWidget::receiveResponse);

        connect(command, &PythonCommand::signalStdErrString,
                command_widget, &ClientCommandWidget::setErrorOutputText);
    }

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<arguments;

    QFuture<void> future = executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    command_widget->setCommandText("loadleveler.py " + arguments.join(" "));

    ProgressItemWidget *progress_item_widget =  ProgressManager::addTask(future, args["command"]);
    progress_item_widget->setDescription("Run shell command: " + args["command"] + " ...");

    qDebug()<<"[LoadLevelerClient::runCommand] end";
}

void LoadLevelerClient::runQueryJobDetailCommand(QMap<QString, QString> args, QPointer<Widgets::JobDetailWidget> widget)
{
    qDebug()<<"[LoadLevelerClient::runQueryJobDetailCommand] start";
    QStringList arguments;
    PythonCommand* command = createPythonCommand();

    if(!widget.isNull())
    {
        connect(command, &PythonCommand::signalStdOutString,
                widget, &Widgets::JobDetailWidget::receiveResponse);

//        connect(command, &PythonCommand::signalStdErrString,
//                command_widget, &ClientCommandWidget::setErrorOutputText);
    }

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<arguments;

    QFuture<void> future = executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    ProgressItemWidget *progress_item_widget =  ProgressManager::addTask(future, args["command"]);
    progress_item_widget->setDescription("Run shell command: " + args["command"] + " ...");

    qDebug()<<"[LoadLevelerClient::runQueryJobDetailCommand] end";
}
