#pragma once

#include "plugin_system_global.h"

#include <QObject>
#include <QString>
#include <QVector>
#include <QPluginLoader>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
class QPluginLoader;
QT_END_NAMESPACE

namespace PluginSystem{

class IPlugin;

struct PLUGIN_SYSTEM_EXPORT PluginDependency
{
public:
    explicit PluginDependency();

    QString name_;
};

class PLUGIN_SYSTEM_EXPORT PluginSpec : public QObject
{
    Q_OBJECT
public:
    explicit PluginSpec(QObject *parent = 0);

    ~PluginSpec();

    bool read(const QString &file_path);

    QString name() const;
    void setName(const QString &name);

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

    // file
    QString file_location_;
    QString file_path_;

    // qt plugin
    QPluginLoader loader_;
    IPlugin* plugin_;

};

}
