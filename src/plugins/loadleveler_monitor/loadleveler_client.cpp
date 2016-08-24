#include "loadleveler_client.h"
#include "loadleveler_monitor_plugin.h"
#include "client_command_widget.h"
#include "panels/llq_panel.h"

#include <python_env_plugin/python_command.h>

#include <QProcess>
#include <QDateTime>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace PythonEnv;

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

//    if(!llq_panel.isNull())
//    {
//        connect(command, &PythonCommand::signalStdOutString,
//                llq_panel, &Panels::LlqPanel::slotReciveResponseStdOut);
//    }

//    connect(command, &PythonCommand::signalStdErrString,
//            [=](const QString &string){
//        qDebug()<<"[LoadLevelerClient::runLlqCommand] error out:"<<string;
//    });

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

    executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );
    qDebug()<<"[LoadLevelerClient::runLlqCommand] end";
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

//    connect(command, &PythonCommand::signalFinished,
//            [=](int exit_code, QProcess::ExitStatus status)
//            {
//                qDebug()<<"[LoadLevelerClient::runCommand] exit code:"<<exit_code;
//                qDebug()<<"[LoadLevelerClient::runCommand] exit status:"<<status;
//            }
//    );

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<arguments;

    executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    command_widget->setCommandText("loadleveler.py " + arguments.join(" "));

    qDebug()<<"[LoadLevelerClient::runCommand] end";
}
