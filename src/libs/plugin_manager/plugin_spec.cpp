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

QString PluginSpec::name() const
{
    return name_;
}

void PluginSpec::setName(const QString &name)
{
    name_ = name;
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

