#pragma once

#include "plugin_system_global.h"

#include <QObject>
#include <QList>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QSplashScreen;
QT_END_NAMESPACE

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

    QList<PluginSpec *> plugins();

    void addObject(QObject *obj);
    void removeObject(QObject *obj);
    QList<QObject *> allObjects();

    void connectSplashScreen(QSplashScreen *screen);
    void disconnectSplashSceen(QSplashScreen *screen);

private:
    void readPluginPaths();
    void resolveDependencies();

    QList<PluginSpec *> loadQueue();

    bool loadQueue(PluginSpec* spec, QList<PluginSpec*> &load_queue, QList<PluginSpec*> &circular_dependency_queue);

    PluginManager *q;

    QList<QObject*> all_objects_;

    QStringList plugin_paths_;

    QList<PluginSpec*> plugin_specs_;
};

}
