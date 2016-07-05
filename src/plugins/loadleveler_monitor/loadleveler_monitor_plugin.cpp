#include "loadleveler_monitor_plugin.h"
#include "loadleveler_monitor_perspective.h"

#include <plugin_manager/plugin_manager.h>

using namespace LoadlevelerMonitor;
using namespace PluginSystem;

LoadlevelerMonitorPlugin::LoadlevelerMonitorPlugin(QObject *parent) :
    IPlugin(parent),
    loadleveler_monitor_perspective_(0)
{
}

LoadlevelerMonitorPlugin::~LoadlevelerMonitorPlugin()
{
    if(loadleveler_monitor_perspective_)
        loadleveler_monitor_perspective_->deleteLater();
}

bool LoadlevelerMonitorPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    loadleveler_monitor_perspective_ = new LoadlevelerMonitorPerspective(this);
    PluginManager::addObject(loadleveler_monitor_perspective_);
    return true;
}

void LoadlevelerMonitorPlugin::pluginsInitialized()
{

}

void LoadlevelerMonitorPlugin::aboutToShutDown()
{

}
