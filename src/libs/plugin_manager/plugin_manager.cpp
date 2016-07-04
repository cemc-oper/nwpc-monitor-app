#include "plugin_manager.h"
#include "plugin_spec.h"

#include <QDir>
#include <QLibrary>
#include <QtDebug>

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

PluginManagerPrivate::PluginManagerPrivate(PluginManager *plugin_manager):
    q(plugin_manager)
{

}

PluginManagerPrivate::~PluginManagerPrivate()
{

}

void PluginManagerPrivate::setPluginPaths(const QStringList &paths)
{
    plugin_paths_ = paths;
    readPluginPaths();
}

void PluginManagerPrivate::loadPlugins()
{
    QString error_string;
    foreach(PluginSpec *plugin_spec, plugin_specs_)
    {
        plugin_spec->loadLibrary();
    }

    foreach(PluginSpec *plugin_spec, plugin_specs_)
    {
        plugin_spec->initializePlugin();
    }
    foreach(PluginSpec *plugin_spec, plugin_specs_)
    {
        plugin_spec->pluginsInitialized();
    }


}

void PluginManagerPrivate::addObject(QObject *obj)
{
    all_objects_.append(obj);
}

void PluginManagerPrivate::removeObject(QObject *obj)
{
    all_objects_.removeAll(obj);
}

QList<QObject *> PluginManagerPrivate::allObjects()
{
    return all_objects_;
}

void PluginManagerPrivate::readPluginPaths()
{
    QStringList plugin_files;

    QStringList search_paths = plugin_paths_;
    while (!search_paths.isEmpty())
    {
        const QDir dir(search_paths.takeFirst());
        const QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
        foreach (const QFileInfo &file, files)
        {
            const QString file_path = file.absoluteFilePath();
            if (QLibrary::isLibrary(file_path))
                plugin_files.append(file_path);
        }
        const QFileInfoList dirs = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
        foreach (const QFileInfo &subdir, dirs)
            search_paths << subdir.absoluteFilePath();
    }


    foreach(QString plugin_file_path, plugin_files)
    {
        PluginSpec* spec = new PluginSpec();
        if(!spec->read(plugin_file_path))
        {
            delete spec;
            continue;
        }
        plugin_specs_.append(spec);
    }

    resolveDependencies();
}

void PluginManagerPrivate::resolveDependencies()
{
    qDebug()<<"[PluginManagerPrivate::resolveDependencies] TODO";
}



