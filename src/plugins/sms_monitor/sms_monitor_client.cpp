#include "sms_monitor_client.h"

#include "sms_monitor_plugin.h"

#include <python_env_plugin/python_command.h>
#include <QApplication>
#include <QtDebug>

using namespace SmsMonitor;
using namespace PythonEnv;


SmsMonitorClient::SmsMonitorClient(QObject *parent):
    PythonEngine(parent)
{

}

SmsMonitorClient::~SmsMonitorClient()
{

}

void SmsMonitorClient::updateStatus()
{
    qDebug()<<"[SmsMonitorClient::updateStatus] start";
    QStringList arguments;
    PythonCommand* command = createPythonCommand();
    connect(command, &PythonCommand::signalStdOutString,
            SmsMonitorPlugin::instance(), &SmsMonitorPlugin::receiveUpdateStatusStdOut);

//    connect(command, &PythonCommand::signalStdErrString,
//            SmsMonitorPlugin::instance(), &SmsMonitorPlugin::receiveUpdateStatusStdOut);

//    connect(command, &PythonCommand::signalFinished,
//            [=](int exit_code, QProcess::ExitStatus status)
//            {
//                qDebug()<<exit_code;
//                qDebug()<<status;
//            }
//    );

    executePythonScript(
        command,
        QApplication::applicationDirPath()+"\\..\\plugins\\sms_monitor\\nwpc_sms_monitor\\update_sms_status.py",
        arguments
    );
    qDebug()<<"[SmsMonitorClient::updateStatus] end";
}

