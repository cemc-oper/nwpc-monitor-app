#include "python_env_plugin.h"

using namespace PythonEnv;
using namespace PluginSystem;

PythonEnvPlugin::PythonEnvPlugin(QObject *parent) :
    IPlugin(parent)
{
}

PythonEnvPlugin::~PythonEnvPlugin()
{

}

bool PythonEnvPlugin::initialize(const QStringList &arguments, QString *error_string)
{
    return true;
}

void PythonEnvPlugin::pluginsInitialized()
{

}

void PythonEnvPlugin::aboutToShutDown()
{

}
