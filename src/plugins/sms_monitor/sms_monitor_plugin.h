#pragma once

#include "sms_monitor_global.h"

#include <plugin_manager/iplugin.h>

namespace SmsMonitor{

class SmsMonitorPerspective;

class SMS_MONITOR_EXPORT SmsMonitorPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "sms_monitor.json")

public:
    SmsMonitorPlugin(QObject *parent = 0);

    ~SmsMonitorPlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();

private:
    SmsMonitorPerspective* sms_monitor_perspective_;
};

}
