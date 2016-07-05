#pragma once

#include "python_env_global.h"

#include <plugin_manager/iplugin.h>

namespace PythonEnv{

class PYTHON_ENV_EXPORT PythonEnvPlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "python_env_plugin.json")
public:
    PythonEnvPlugin(QObject *parent = 0);

    ~PythonEnvPlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();
};
}
