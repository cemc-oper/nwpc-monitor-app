#pragma once

#include "loadleveler_monitor_global.h"

#include <plugin_manager/iplugin.h>

namespace LoadlevelerMonitor{

class LoadlevelerMonitorPerspective;

class LOADLEVELER_MONITOR_EXPORT LoadlevelerMonitorPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "loadleveler_monitor.json")

public:
    LoadlevelerMonitorPlugin(QObject *parent = 0);

    ~LoadlevelerMonitorPlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();

private:
    LoadlevelerMonitorPerspective* loadleveler_monitor_perspective_;
};

}
