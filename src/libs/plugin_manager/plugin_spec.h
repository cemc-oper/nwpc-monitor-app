#pragma once

#include "plugin_system_global.h"

#include <QObject>
#include <QString>
#include <QVector>
#include <QHash>
#include <QPluginLoader>
#include <QJsonObject>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QPluginLoader;
QT_END_NAMESPACE

namespace PluginSystem{

class IPlugin;

struct PLUGIN_SYSTEM_EXPORT PluginDependency
{
public:
    explicit PluginDependency();

    bool operator ==(const PluginDependency &other) const;

    QString name_;
};

uint qHash(const PluginSystem::PluginDependency &value);

class PLUGIN_SYSTEM_EXPORT PluginSpec : public QObject
{
    Q_OBJECT
public:
    explicit PluginSpec(QObject *parent = 0);

    ~PluginSpec();

    bool satisfyDependency(const PluginDependency& dependency) const;

    bool read(const QString &file_path);
    bool resolveDependencies(const QList<PluginSpec*> &specs);

    QString name() const;
    void setName(const QString &name);

    QHash<PluginDependency, PluginSpec *> dependencyPluginSpecs() const;

    IPlugin *plugin();

    // Step 1. load
    bool loadLibrary();

    // Step 2. initialize
    bool initializePlugin();

    // Step 3. pluginsInitialized
    bool pluginsInitialized();

signals:

public slots:

private:
    bool readMetaData(const QJsonObject &meta_data);

    QString name_;
    QVector<PluginDependency> dependency_list_;
    QHash<PluginDependency, PluginSpec*> dependency_plugin_specs_;

    // file
    QString file_location_;
    QString file_path_;

    // qt plugin
    QPluginLoader loader_;
    QPointer<IPlugin> plugin_;
};

}
