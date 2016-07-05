#pragma once

#include "welcome_plugin_global.h"

#include <plugin_manager/iplugin.h>

namespace Welcome{

class WelcomePerspective;

class WELCOME_PLUGIN_EXPORT WelcomePlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "welcome_plugin.json")

public:
    WelcomePlugin(QObject *parent = 0);
    ~WelcomePlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();

private:
     WelcomePerspective* welcome_perspective_;

};

}
