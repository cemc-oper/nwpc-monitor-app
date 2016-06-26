#include "iplugin.h"

#include "plugin_manager.h"

IPlugin::IPlugin(QObject *parent) : QObject(parent)
{

}

IPlugin::~IPlugin()
{

}

void IPlugin::addObject(QObject *obj)
{
    PluginManager::addObject(obj);
}

void IPlugin::removeObject(QObject *obj)
{
    PluginManager::removeObject(obj);
}
