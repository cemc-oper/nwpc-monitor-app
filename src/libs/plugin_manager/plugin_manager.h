#pragma once

#include "iplugin.h"

#include <QObject>
#include <QList>

namespace PluginSystem{

class PluginSpec;

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

    static QList<QObject *> allObjects();

    template <typename T> static QList<T *> getObjects()
    {
        QList<T *> results;
        QList<QObject *> all = allObjects();
        foreach (QObject *obj, all) {
            T *result = qobject_cast<T *>(obj);
            if (result)
                results += result;
        }
        return results;
    }

    friend class PluginManagerPrivate;
};

}
