#pragma once

#include "plugin_system_global.h"
#include "plugin_manager_private.h"

#include <QObject>
#include <QVector>
#include <QList>
#include <QStringList>

namespace PluginSystem{

class PluginManager;
class PluginSpec;

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

    QList<QObject *> allObjects();

private:
    void readPluginPaths();
    void resolveDependencies();

    PluginManager *q;

    QList<QObject*> all_objects_;

    QStringList plugin_paths_;

    QVector<PluginSpec*> plugin_specs_;

    QObject* a;

};

}
