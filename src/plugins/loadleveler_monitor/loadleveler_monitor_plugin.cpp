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
#include <QApplication>
#include <QDir>
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

    //NOTE(windroc, 2016.11.24): use vendor dir.
    QString python_interpreter_dir = QApplication::applicationDirPath() + "/../vendor/python";
    QString python_exe_dir = python_interpreter_dir + "/python.exe";
    loadleveler_client_->setPythonDistributionDir(python_interpreter_dir);
    loadleveler_client_->setPythonExecutableProgramPath(python_exe_dir);

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
