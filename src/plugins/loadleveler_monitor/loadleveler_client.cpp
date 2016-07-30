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

void LoadLevelerClient::runLlqCommand()
{
    qDebug()<<"[LoadLevelerClient::runLlqCommand] start";
    QStringList arguments;
    PythonCommand* command = createPythonCommand();
    connect(command, &PythonCommand::signalStdOutString,
            LoadLevelerMonitorPlugin::instance(), &LoadLevelerMonitorPlugin::receiveLlqQueryStdOut);

    connect(command, &PythonCommand::signalStdErrString,
            [=](const QString &string){
        qDebug()<<string;
    });

    connect(command, &PythonCommand::signalFinished,
            [=](int exit_code, QProcess::ExitStatus status)
            {
                qDebug()<<exit_code;
                qDebug()<<status;
            }
    );

    arguments<<"llq";
    arguments<<"-H uranus.hpc.nmic.cn";
    arguments<<"-u wangdp";
    arguments<<"-p perilla";
    arguments<<"-c llq";

    executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );
    qDebug()<<"[LoadLevelerClient::updateStatus] end";
}
