#pragma once

#include "loadleveler_monitor_global.h"

#include <plugin_manager/iplugin.h>

#include <QPointer>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPerspective;
class LoadLevelerClient;

namespace Model{
class LlqCommandManager;
class LlclassCommandManager;
}

class LOADLEVELER_MONITOR_EXPORT LoadLevelerMonitorPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "loadleveler_monitor.json")

public:
    LoadLevelerMonitorPlugin(QObject *parent = nullptr);
    ~LoadLevelerMonitorPlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();

    static LoadLevelerMonitorPlugin *instance();
    static LoadLevelerClient *client();

public slots:

private:
    QPointer<LoadLevelerMonitorPerspective> loadleveler_monitor_perspective_;
    QPointer<LoadLevelerClient> loadleveler_client_;
    QPointer<Model::LlqCommandManager> llq_command_manager_;
    QPointer<Model::LlclassCommandManager> llclass_command_manager_;

};

}
