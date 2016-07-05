#include "plugin_spec.h"
#include "iplugin.h"

#include <QPluginLoader>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtDebug>

using namespace PluginSystem;

PluginDependency::PluginDependency()
{

}

bool PluginDependency::operator ==(const PluginDependency &other) const
{
    bool flag = true;
    if(name_ != other.name_)
        flag = false;
    return flag;
}

uint PluginSystem::qHash(const PluginSystem::PluginDependency &value)
{
    return qHash(value.name_);
}



PluginSpec::PluginSpec(QObject *parent) :
    QObject(parent),
    loader_(this),
    plugin_(0)
{

}

PluginSpec::~PluginSpec()
{
    loader_.deleteLater();
}

bool PluginSpec::satisfyDependency(const PluginDependency &dependency) const
{
    if(dependency.name_ != name_)
        return false;

    return true;
}

bool PluginSpec::read(const QString &file_path)
{
    QFileInfo file_info(file_path);
    file_location_ = file_info.absolutePath();
    file_path_ = file_info.absoluteFilePath();

    if(!file_info.exists())
    {
        qDebug()<<"[PluginSpec::read] plugin file doesn't exist."<<file_path;
        return false;
    }

    loader_.setFileName(file_path);

    if(!readMetaData(loader_.metaData()))
    {
        qDebug()<<"[PluginSpec::read] failed read meta data.";
        return false;
    }

    return true;
}

bool PluginSpec::resolveDependencies(const QList<PluginSpec *> &specs)
{
    QHash<PluginDependency, PluginSpec*> dependency_plugins;
    foreach(PluginDependency dependency, dependency_list_)
    {
        bool flag = false;
        PluginSpec* dep_spec = 0;
        foreach(PluginSpec* spec, specs)
        {
            if(spec->satisfyDependency(dependency))
            {
                flag = true;
                dep_spec = spec;
                break;
            }
        }
        if(!flag)
        {
            qDebug()<<"[PluginSpec::resolveDependencies] can't find dependency plugin for "<<name_;
            return false;
        }
        dependency_plugins.insert(dependency, dep_spec);
    }
    dependency_plugin_specs_ = dependency_plugins;
}

QString PluginSpec::name() const
{
    return name_;
}

void PluginSpec::setName(const QString &name)
{
    name_ = name;
}

QHash<PluginDependency, PluginSpec *> PluginSpec::dependencyPluginSpecs() const
{
    return dependency_plugin_specs_;
}

IPlugin *PluginSpec::plugin()
{
    return plugin_;
}

bool PluginSpec::loadLibrary()
{
    if(!loader_.load())
    {
        qDebug()<<"[PluginSpec::loadLibrary] Can't load plugin"<<name_;
        return false;
    }

    QObject *a = loader_.instance();
    IPlugin *plugin_object = qobject_cast<IPlugin*>(a);
    if (!plugin_object)
    {
        qDebug()<<"[PluginSpec::loadLibrary] Can't load IPlugin object in plugin"<< name_;
        loader_.unload();
        return false;
    }
    plugin_ = plugin_object;
    return true;
}

bool PluginSpec::initializePlugin()
{
    QStringList arguments;
    QString error_string;
    if (!plugin_->initialize(arguments, &error_string)) {
        qDebug()<<"[PluginSpec::pluginsInitialized] failed: "<< error_string;
        return false;
    }
    return true;
}

bool PluginSpec::pluginsInitialized()
{
    plugin_->pluginsInitialized();
    return true;
}

bool PluginSpec::readMetaData(const QJsonObject &meta_data)
{
    qDebug()<<QJsonDocument(meta_data).toJson();
    QJsonValue value;

    value = meta_data.value(QLatin1String("MetaData"));
    if(!value.isObject())
    {
        qDebug()<<"[PluginSpec::readMetaData] Plugin MetaData not found.";
        return false;
    }
    QJsonObject plugin_meta_data = value.toObject();

    value = plugin_meta_data.value(QLatin1String("name"));
    if(value.isUndefined() || !value.isString())
    {
        qDebug()<<"[PluginSpec::readMetaData] name has error.";
        return false;
    }
    name_ = value.toString();

    value = plugin_meta_data.value(QLatin1String("dependencies"));
    if(value.isUndefined() || !value.isArray())
    {
        qDebug()<<"[PluginSpec::readMetaData] dependencies has error.";
        return false;
    }
    {
        QJsonArray array = value.toArray();
        foreach (const QJsonValue &v, array)
        {
            if (!v.isObject())
            {
                qDebug()<<"[PluginSpec::readMetaData] a dependency entry is not object.";
                return false;
            }
            QJsonObject dependency_object = v.toObject();
            PluginDependency dep;

            value = dependency_object.value(QLatin1Literal("name"));
            if(value.isUndefined() || !value.isString())
            {
                qDebug()<<"[PluginSpec::readMetaData] a dependency entry's name has an error.";
                return false;
            }
            dep.name_ = value.toString();

            dependency_list_.append(dep);
        }
    }

    return true;
}
