#pragma once

#include "loadleveler_monitor_global.h"

#include <plugin_manager/iplugin.h>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPerspective;

class LOADLEVELER_MONITOR_EXPORT LoadLevelerMonitorPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "loadleveler_monitor.json")

public:
    LoadLevelerMonitorPlugin(QObject *parent = 0);

    ~LoadLevelerMonitorPlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();

private:
    LoadLevelerMonitorPerspective* loadleveler_monitor_perspective_;
};

}
