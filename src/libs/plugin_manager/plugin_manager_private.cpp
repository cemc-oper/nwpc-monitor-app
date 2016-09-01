#include "plugin_manager_private.h"
#include "plugin_manager.h"

#include "plugin_spec.h"

#include <QDir>
#include <QFileInfo>
#include <QLibrary>
#include <QListIterator>
#include <QSplashScreen>
#include <QtDebug>

using namespace PluginSystem;

PluginManagerPrivate::PluginManagerPrivate(PluginManager *plugin_manager):
    q(plugin_manager)
{

}

PluginManagerPrivate::~PluginManagerPrivate()
{
    qDeleteAll(plugin_specs_);
}

void PluginManagerPrivate::setPluginPaths(const QStringList &paths)
{
    plugin_paths_ = paths;
    readPluginPaths();
}

void PluginManagerPrivate::loadPlugins()
{
    QList<PluginSpec*> load_queue = loadQueue();

    QString error_string;
    foreach(PluginSpec *plugin_spec, load_queue)
    {
        emit q->signalSplashMessageChanged("Loading plugin's library..." + plugin_spec->name());
        plugin_spec->loadLibrary();
    }

    foreach(PluginSpec *plugin_spec, load_queue)
    {
        emit q->signalSplashMessageChanged("Initializing plugin..." + plugin_spec->name());
        plugin_spec->initializePlugin();
    }

    QListIterator<PluginSpec*> iter(load_queue);
    iter.toBack();
    while(iter.hasPrevious())
    {
        PluginSpec *plugin_spec = iter.previous();
        emit q->signalSplashMessageChanged("Finishing plugin loading..." + plugin_spec->name());
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

void PluginManagerPrivate::connectSplashScreen(QSplashScreen *screen)
{
    connect(q, &PluginManager::signalSplashMessageChanged,
            [=](const QString &message){
        screen->showMessage(message);
    });
}

void PluginManagerPrivate::disconnectSplashSceen(QSplashScreen *screen)
{
    disconnect(q, &PluginManager::signalSplashMessageChanged, 0, 0);
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
            qDebug()<<"[PluginManagerPrivate::readPluginPaths] can't read plugin spec"<<plugin_file_path;
            delete spec;
            continue;
        }
        plugin_specs_.append(spec);
    }

    resolveDependencies();
}

void PluginManagerPrivate::resolveDependencies()
{
    //qDebug()<<"[PluginManagerPrivate::resolveDependencies] ";
    foreach(PluginSpec* spec, plugin_specs_)
    {
        spec->resolveDependencies(plugin_specs_);
    }
    return;
}

QList<PluginSpec *> PluginManagerPrivate::loadQueue()
{
    QList<PluginSpec *> load_queue;
    foreach(PluginSpec *spec, plugin_specs_)
    {
        QList<PluginSpec *> circular_dependency_queue;
        loadQueue(spec, load_queue, circular_dependency_queue);
    }
    return load_queue;
}

bool PluginManagerPrivate::loadQueue(PluginSpec *spec, QList<PluginSpec *> &load_queue, QList<PluginSpec *> &circular_dependency_queue)
{
    // 已经处理完依赖关系，并在加载队列中，不需要再一次解决依赖关系
    if(load_queue.contains(spec))
    {
        return true;
    }

    /*
     只有在处理完依赖关系后，该PluginSpec才会被放入load_queue中。
     如果在处理依赖关系时，再一次出现PluginSpec，就出现循环依赖问题。
     */

    // 循环加载的情况
    if(circular_dependency_queue.contains(spec))
    {
        qDebug()<<"[PluginManagerPrivate::loadQueue] Circular dependency detected:"<<spec->name();
        return false;
    }

    circular_dependency_queue.append(spec);

    QHashIterator<PluginDependency, PluginSpec*> iter(spec->dependencyPluginSpecs());
    while(iter.hasNext())
    {
        iter.next();

        PluginSpec* dependency_spec = iter.value();
        if(!loadQueue(dependency_spec, load_queue, circular_dependency_queue))
        {
            qDebug()<<"[PluginManagerPrivate::loadQueue] can't load plugin"<<spec->name()
                  <<"because dependency plugin"<<dependency_spec->name()<<"load failed.";
            return false;
        }
    }

    load_queue.append(spec);

    return true;

}
