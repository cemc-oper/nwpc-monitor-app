#include "iplugin.h"
#include "plugin_spec.h"
#include "plugin_manager.h"

using namespace PluginSystem;

IPlugin::IPlugin(QObject *parent) :
    QObject(parent),
    plugin_spec_{0}
{

}

IPlugin::~IPlugin()
{

}

PluginSpec *IPlugin::pluginSpec()
{
    return plugin_spec_;
}

void IPlugin::addObject(QObject *obj)
{
    PluginManager::addObject(obj);
}

void IPlugin::removeObject(QObject *obj)
{
    PluginManager::removeObject(obj);
}
