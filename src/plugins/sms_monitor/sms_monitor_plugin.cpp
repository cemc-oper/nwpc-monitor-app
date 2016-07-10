#include "sms_monitor_plugin.h"
#include "sms_monitor_perspective.h"
#include "sms_monitor_client.h"
#include "sms_monitor_widget.h"

#include "sms_model/bunch.h"

#include <plugin_manager/plugin_manager.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace SmsMonitor;
using namespace SmsMonitor::SmsModel;
using namespace PluginSystem;

SmsMonitorPlugin* sms_monitor_plugin_instance = nullptr;

SmsMonitorPlugin::SmsMonitorPlugin(QObject *parent) :
    IPlugin(parent),
    sms_monitor_perspective_{nullptr},
    sms_monitor_client_{nullptr}
{
    sms_monitor_plugin_instance = this;
}

SmsMonitorPlugin::~SmsMonitorPlugin()
{
    if(sms_monitor_perspective_)
        sms_monitor_perspective_->deleteLater();
    if(sms_monitor_client_)
        sms_monitor_client_->deleteLater();
    sms_monitor_plugin_instance = nullptr;
}

bool SmsMonitorPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    sms_monitor_perspective_ = new SmsMonitorPerspective{this};
    PluginManager::addObject(sms_monitor_perspective_);

    sms_monitor_client_ = new SmsMonitorClient{this};
    PluginManager::addObject(sms_monitor_client_);

    //TODO(windroc, 2016.07.08): use plugin dir.
    sms_monitor_client_->setPythonDistributionDir(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35"
    );
    sms_monitor_client_->setPythonExecutableProgramPath(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35\\python.exe"
    );

    return true;
}

void SmsMonitorPlugin::pluginsInitialized()
{

}

void SmsMonitorPlugin::aboutToShutDown()
{

}


SmsMonitorPlugin *SmsMonitorPlugin::instance()
{
    return sms_monitor_plugin_instance;
}

SmsMonitorClient *SmsMonitorPlugin::client()
{
    return sms_monitor_plugin_instance->sms_monitor_client_;
}

void SmsMonitorPlugin::slotUpdateSmsStatus()
{

}

void SmsMonitorPlugin::receiveUpdateStatusStdOut(const QString &out)
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

    Bunch* bunch = Bunch::buildFromJsonStatus(data);
    sms_monitor_perspective_->widget()->setBunch(bunch);

    qDebug()<<owner<<repo;
    sms_monitor_perspective_->widget()->showMessageOnMessagePanel(owner+"/"+repo);

}

