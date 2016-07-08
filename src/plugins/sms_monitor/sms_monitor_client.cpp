#include "sms_monitor_client.h"

#include <python_env_plugin/python_command.h>

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
    connect(command, &PythonCommand::signalStdOutString, this, &SmsMonitorClient::slotUpdateStatusStdOut);

    executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\sms_monitor\\nwpc_sms_monitor\\update_sms_status.py",
        arguments
    );
    qDebug()<<"[SmsMonitorClient::updateStatus] end";
}

void SmsMonitorClient::slotUpdateStatusStdOut(const QString &out)
{
    qDebug()<<out;
}
