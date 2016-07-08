#include "sms_monitor_client.h"

#include <python_env_plugin/python_command.h>

#include <QJsonDocument>
#include <QJsonObject>
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

    connect(command, &PythonCommand::signalStdErrString, this, &SmsMonitorClient::slotUpdateStatusStdOut);

    connect(command, &PythonCommand::signalFinished,
            [=](int exit_code, QProcess::ExitStatus status)
            {
                qDebug()<<exit_code;
                qDebug()<<status;
            }
    );

    executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\sms_monitor\\nwpc_sms_monitor\\update_sms_status.py",
        arguments
    );
    qDebug()<<"[SmsMonitorClient::updateStatus] end";
}

void SmsMonitorClient::slotUpdateStatusStdOut(const QString &out)
{
    QString result_str = out;
    QJsonDocument doc = QJsonDocument::fromJson(result_str.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"result is not a json string.";
    }
    QJsonObject result_object = doc.object();

    if( result_object.contains("error"))
    {
        QString cdp_error_message = result_object["data"].toObject()["message"].toString();
        qDebug()<<"ERROR:"<<cdp_error_message;
        return;
    }

    QString app = result_object["app"].toString();
    QString type = result_object["type"].toString();
    QJsonObject data = result_object["data"].toObject();
    QString owner = data["owner"].toString();
    QString repo = data["repo"].toString();
    QString sms_name = data["sms_name"].toString();
    QString sms_user = data["sms_user"].toString();
    QString time = data["time"].toString();
    QJsonObject status = data["status"].toObject();
    qDebug()<<owner<<repo;

}
