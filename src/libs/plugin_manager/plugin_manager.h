#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "iplugin.h"

#include <QObject>
#include <QList>
#include <QPluginLoader>

class PLUGIN_SYSTEM_EXPORT PluginManager: public QObject
{
    Q_OBJECT
public:
    static PluginManager* instance();

    PluginManager();
    ~PluginManager();

    static void setPluginPaths(const QStringList& paths);

    static void loadPlugins();

    static void addObject(QObject* obj);
    static void removeObject(QObject *obj);

    friend class PluginManagerPrivate;
};

class PLUGIN_SYSTEM_EXPORT PluginManagerPrivate: public QObject
{
    Q_OBJECT
public:
    PluginManagerPrivate(PluginManager* plugin_manager);
    ~PluginManagerPrivate();

    void setPluginPaths(const QStringList& paths);

    void loadPlugins();

    void addObject(QObject *obj);

    void removeObject(QObject *obj);


private:
    PluginManager *q;

    QList<QObject*> all_objects_;

    QStringList plugin_paths_;

    QPluginLoader loader_;

    QList<IPlugin*> plugins_;

    QObject* a;

};


#endif // PLUGIN_MANAGER_H
