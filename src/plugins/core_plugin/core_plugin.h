#pragma once

#include "core_plugin_global.h"

#include <plugin_manager/iplugin.h>

namespace Core{

class MainWindow;
class WelcomePerspective;
class ActionManager;

class CorePlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "core_plugin.json")

public:
    CorePlugin(QObject *parent = 0);
    ~CorePlugin();

    bool initialize(const QStringList& arguments, QString* error_string);

    void pluginsInitialized();

    void aboutToShutDown();

private:
    MainWindow *main_window_;

    //add for test
    WelcomePerspective *welcome_perspective_;

    ActionManager *action_manager_;
};

}
