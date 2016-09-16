#include "loadleveler_monitor_plugin.h"
#include "loadleveler_monitor_perspective.h"
#include "loadleveler_client.h"
#include "loadleveler_monitor_widget.h"
#include "model/query_model.h"
#include "model/llq_command_manager.h"
#include "model/llclass_command_manager.h"

#include <plugin_manager/plugin_manager.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Model;
using namespace PluginSystem;

LoadLevelerMonitorPlugin* loadleveler_monitor_plugin_instance = nullptr;

LoadLevelerMonitorPlugin::LoadLevelerMonitorPlugin(QObject *parent) :
    IPlugin{parent},
    loadleveler_monitor_perspective_{nullptr},
    llq_command_manager_{nullptr}
{
    loadleveler_monitor_plugin_instance = this;
}

LoadLevelerMonitorPlugin::~LoadLevelerMonitorPlugin()
{
    if(loadleveler_monitor_perspective_)
        loadleveler_monitor_perspective_->deleteLater();
    if(loadleveler_client_)
        loadleveler_client_->deleteLater();
    if(llq_command_manager_)
        llq_command_manager_->deleteLater();
    loadleveler_monitor_plugin_instance = nullptr;
}

bool LoadLevelerMonitorPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    loadleveler_monitor_perspective_ = new LoadLevelerMonitorPerspective(this);
    PluginManager::addObject(loadleveler_monitor_perspective_);

    loadleveler_client_ = new LoadLevelerClient{this};
    PluginManager::addObject(loadleveler_client_);

    //TODO(windroc, 2016.07.08): use plugin dir.
    loadleveler_client_->setPythonDistributionDir(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35"
    );
    loadleveler_client_->setPythonExecutableProgramPath(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35\\python.exe"
    );

    llq_command_manager_ = new LlqCommandManager{this};
    LlqCommandManager::initialize();

    llclass_command_manager_ = new LlclassCommandManager{this};
    LlclassCommandManager::initialize();

    return true;
}

void LoadLevelerMonitorPlugin::pluginsInitialized()
{

}

void LoadLevelerMonitorPlugin::aboutToShutDown()
{

}

LoadLevelerMonitorPlugin *LoadLevelerMonitorPlugin::instance()
{
    return loadleveler_monitor_plugin_instance;
}

LoadLevelerClient *LoadLevelerMonitorPlugin::client()
{
    return loadleveler_monitor_plugin_instance->loadleveler_client_;
}
