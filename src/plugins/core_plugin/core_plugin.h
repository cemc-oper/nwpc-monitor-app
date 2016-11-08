#pragma once

#include "core_plugin_global.h"

#include <plugin_manager/iplugin.h>

namespace Core{

class MainWindow;
class WelcomePerspective;
class ActionManager;

namespace ViewSystem{
class ViewManager;
class ViewSpec;
class DockWidget;
}

namespace PerspectiveSystem{
class PerspectiveManager;
}

namespace ProgressSystem{
class ProgressManager;
}

namespace SessionSystem{
class SessionManager;
}

class CORE_PLUGIN_EXPORT CorePlugin : public PluginSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "core_plugin.json")

public:
    CorePlugin(QObject *parent = 0);
    ~CorePlugin();

    bool initialize(const QStringList& arguments, QString* error_string);
    void pluginsInitialized();
    void aboutToShutDown();

    SessionSystem::SessionManager *sessionManager() const;

private:
    void initActionSystem();
    void initMainWindow();
    void initViewSystem();
    void initProgressSystem();
    void initSessionSystem();

    void initViewSpec(ViewSystem::ViewSpec *view_spec, ViewSystem::DockWidget *dock_widget);

    QPointer<MainWindow> main_window_;

    //add for test
    QPointer<WelcomePerspective> welcome_perspective_;

    QPointer<ActionManager> action_manager_;
    QPointer<ViewSystem::ViewManager> view_manager_;
    QPointer<PerspectiveSystem::PerspectiveManager> perspective_manager_;
    QPointer<ProgressSystem::ProgressManager> progress_manager_;
    QPointer<SessionSystem::SessionManager> session_manager_;
};

}
