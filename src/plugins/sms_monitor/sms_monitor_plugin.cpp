#include "sms_monitor_plugin.h"
#include "sms_monitor_perspective.h"

#include <plugin_manager/plugin_manager.h>

using namespace SmsMonitor;
using namespace PluginSystem;

SmsMonitorPlugin::SmsMonitorPlugin(QObject *parent) :
    IPlugin(parent),
    sms_monitor_perspective_(0)
{
}

SmsMonitorPlugin::~SmsMonitorPlugin()
{
    if(sms_monitor_perspective_)
        sms_monitor_perspective_->deleteLater();
}

bool SmsMonitorPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    sms_monitor_perspective_ = new SmsMonitorPerspective(this);
    PluginManager::addObject(sms_monitor_perspective_);
    return true;
}

void SmsMonitorPlugin::pluginsInitialized()
{

}

void SmsMonitorPlugin::aboutToShutDown()
{

}
