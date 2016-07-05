#include "plugin_manager.h"
#include "plugin_manager_private.h"

using namespace PluginSystem;

static PluginManager *plugin_manager_instance = 0;
static PluginManagerPrivate *d = 0;

PluginManager *PluginManager::instance()
{
    return plugin_manager_instance;
}

PluginManager::PluginManager():
    QObject(0)
{
    plugin_manager_instance = this;
    d = new PluginManagerPrivate(this);
}

PluginManager::~PluginManager()
{
    d->deleteLater();
    d = 0;
}

void PluginManager::setPluginPaths(const QStringList &paths)
{
    d->setPluginPaths(paths);
}

void PluginManager::loadPlugins()
{
    d->loadPlugins();
}

void PluginManager::addObject(QObject *obj)
{
    d->addObject(obj);
}

void PluginManager::removeObject(QObject *obj)
{
    d->removeObject(obj);
}

QList<QObject *> PluginManager::allObjects()
{
    return d->allObjects();
}



