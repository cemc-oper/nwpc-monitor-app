#include "loadleveler_client.h"

#include "loadleveler_monitor_plugin.h"

#include <python_env_plugin/python_command.h>

#include <QProcess>
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

void LoadLevelerClient::runLlqCommand(QMap<QString, QString> args)
{
    qDebug()<<"[LoadLevelerClient::runLlqCommand] start";
    QStringList arguments;
    PythonCommand* command = createPythonCommand();
    connect(command, &PythonCommand::signalStdOutString,
            LoadLevelerMonitorPlugin::instance(), &LoadLevelerMonitorPlugin::receiveLlqQueryStdOut);

    connect(command, &PythonCommand::signalStdErrString,
            [=](const QString &string){
        qDebug()<<"[LoadLevelerClient::runLlqCommand] error out:"<<string;
    });

    connect(command, &PythonCommand::signalFinished,
            [=](int exit_code, QProcess::ExitStatus status)
            {
                qDebug()<<"[LoadLevelerClient::runLlqCommand] exit code:"<<exit_code;
                qDebug()<<"[LoadLevelerClient::runLlqCommand] exit status:"<<status;
            }
    );

    arguments<<"llq";
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
    qDebug()<<"[LoadLevelerClient::runLlqCommand] end";
}
