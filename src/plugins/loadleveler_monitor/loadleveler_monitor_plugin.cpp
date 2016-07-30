#include "loadleveler_monitor_plugin.h"
#include "loadleveler_monitor_perspective.h"

#include <plugin_manager/plugin_manager.h>

using namespace LoadLevelerMonitor;
using namespace PluginSystem;

LoadLevelerMonitorPlugin::LoadLevelerMonitorPlugin(QObject *parent) :
    IPlugin(parent),
    loadleveler_monitor_perspective_(0)
{
}

LoadLevelerMonitorPlugin::~LoadLevelerMonitorPlugin()
{
    if(loadleveler_monitor_perspective_)
        loadleveler_monitor_perspective_->deleteLater();
}

bool LoadLevelerMonitorPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    loadleveler_monitor_perspective_ = new LoadLevelerMonitorPerspective(this);
    PluginManager::addObject(loadleveler_monitor_perspective_);
    return true;
}

void LoadLevelerMonitorPlugin::pluginsInitialized()
{

}

void LoadLevelerMonitorPlugin::aboutToShutDown()
{

}
