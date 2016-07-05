#include "welcome_plugin.h"
#include "welcome_perspective.h"

#include <plugin_manager/plugin_manager.h>

using namespace Welcome;

WelcomePlugin::WelcomePlugin(QObject *parent) :
    IPlugin(parent),
    welcome_perspective_(0)
{

}

WelcomePlugin::~WelcomePlugin()
{

}

bool WelcomePlugin::initialize(const QStringList &arguments, QString *error_string)
{
    // add for test
    welcome_perspective_ = new WelcomePerspective(this);
    PluginSystem::PluginManager::addObject(welcome_perspective_);
    return true;
}

void WelcomePlugin::pluginsInitialized()
{

}

void WelcomePlugin::aboutToShutDown()
{

}

