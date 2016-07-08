#include "sms_monitor_plugin.h"
#include "sms_monitor_perspective.h"
#include "sms_monitor_client.h"

#include <plugin_manager/plugin_manager.h>

using namespace SmsMonitor;
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

