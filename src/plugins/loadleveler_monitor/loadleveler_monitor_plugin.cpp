#include "loadleveler_monitor_plugin.h"
#include "loadleveler_monitor_perspective.h"
#include "loadleveler_client.h"
#include "loadleveler_monitor_widget.h"
#include "loadleveler_model/job_query_model.h"

#include <plugin_manager/plugin_manager.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::LoadLevelerModel;
using namespace PluginSystem;

LoadLevelerMonitorPlugin* loadleveler_monitor_plugin_instance = nullptr;

LoadLevelerMonitorPlugin::LoadLevelerMonitorPlugin(QObject *parent) :
    IPlugin{parent},
    loadleveler_monitor_perspective_{0}
{
    loadleveler_monitor_plugin_instance = this;
}

LoadLevelerMonitorPlugin::~LoadLevelerMonitorPlugin()
{
    if(loadleveler_monitor_perspective_)
        loadleveler_monitor_perspective_->deleteLater();
    if(loadleveler_client_)
        loadleveler_client_->deleteLater();
    loadleveler_monitor_plugin_instance = nullptr;
}

bool LoadLevelerMonitorPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    loadleveler_monitor_perspective_ = new LoadLevelerMonitorPerspective(this);
    PluginManager::addObject(loadleveler_monitor_perspective_);

    loadleveler_client_ = new LoadLevelerClient{this};
    PluginManager::addObject(loadleveler_client_);

    //TODO(windroc, 2016.07.08): use plugin dir.
    loadleveler_client_->setPythonDistributionDir(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35"
    );
    loadleveler_client_->setPythonExecutableProgramPath(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35\\python.exe"
    );
    return true;
}

void LoadLevelerMonitorPlugin::pluginsInitialized()
{

}

void LoadLevelerMonitorPlugin::aboutToShutDown()
{

}

LoadLevelerMonitorPlugin *LoadLevelerMonitorPlugin::instance()
{
    return loadleveler_monitor_plugin_instance;
}

LoadLevelerClient *LoadLevelerMonitorPlugin::client()
{
    return loadleveler_monitor_plugin_instance->loadleveler_client_;
}

void LoadLevelerMonitorPlugin::receiveLlqQueryStdOut(const QString &out)
{
    qDebug()<<"[LoadLevelerMonitorPlugin::receiveLlqQueryStdOut] start";
    QString result_str = out;
    qDebug()<<"[LoadLevelerMonitorPlugin::receiveLlqQueryStdOut] llq query std out:"<<result_str;

    QJsonDocument doc = QJsonDocument::fromJson(result_str.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LoadLevelerMonitorPlugin::receiveLlqQueryStdOut] result is not a json string.";
    }
    QJsonObject result_object = doc.object();

    if( result_object.contains("error"))
    {
        QString cdp_error_message = result_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LoadLevelerMonitorPlugin::receiveLlqQueryStdOut] ERROR:"<<cdp_error_message;
        return;
    }

    QString app = result_object["app"].toString();
    QString type = result_object["type"].toString();

    QJsonObject data = result_object["data"].toObject();

    JobQueryModel* model = JobQueryModel::buildFromLlqQuery(data);
    loadleveler_monitor_perspective_->widget()->setJobQueryModel(model);

    qDebug()<<"[LoadLevelerMonitorPlugin::receiveLlqQueryStdOut] end";
}
