#include "plugin_manager.h"

#include <QDir>
#include <QtDebug>

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
}

void PluginManagerPrivate::loadPlugins()
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
    a = 0;
    foreach(QString plugin_file_path, plugin_files)
    {
        loader_.setFileName(plugin_file_path);
        if(loader_.load())
        {
            a = loader_.instance();
//            qDebug()<<a->objectName();
            IPlugin *plugin_object = qobject_cast<IPlugin*>(a);
            if (!plugin_object)
            {
                qDebug()<<"Plugin load failed:"<< plugin_file_path;
                loader_.unload();
                continue;
            }
            plugins_.append(plugin_object);
        }
    }
    QString error_string;
    foreach(IPlugin *a_plugin, plugins_)
    {
        a_plugin->initialize(QStringList(), &error_string);
    }

    foreach(IPlugin *a_plugin, plugins_)
    {
        a_plugin->pluginsInitialized();
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



