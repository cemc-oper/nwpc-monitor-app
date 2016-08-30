#include "core_plugin.h"

#include "mainwindow.h"
#include "action_system/action_manager.h"
#include "view_system/view_manager.h"
#include "views/console_dock_widget.h"
#include "views/progress_dock_widget.h"
#include "view_system/view_spec.h"
#include "view_system/dock_view.h"
#include "perspective_system/perspective_manager.h"
#include "progress_system/progress_manager.h"
#include "progress_system/progress_view.h"

#include <plugin_manager/plugin_manager.h>

using namespace Core;
using namespace PluginSystem;
using namespace Core::Views;
using namespace Core::ViewSystem;
using namespace Core::PerspectiveSystem;
using namespace Core::ProgressSystem;

CorePlugin::CorePlugin(QObject *parent) :
    IPlugin(parent),
    main_window_(nullptr),
    action_manager_{nullptr},
    view_manager_{nullptr},
    perspective_manager_{nullptr},
    progress_manager_{nullptr}
{
}

CorePlugin::~CorePlugin()
{
    delete main_window_;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *error_string)
{
    perspective_manager_ = new PerspectiveManager{this};

    initActionSystem();
    initMainWindow();
    initViewSystem();
    initProgressSystem();
    return true;
}

void CorePlugin::pluginsInitialized()
{
    main_window_->loadPerspectives();

    main_window_->loadViews();

    main_window_->activatePerspective("welcome");

    main_window_->show();
}

void CorePlugin::aboutToShutDown()
{
    main_window_->hide();
}

void CorePlugin::initActionSystem()
{
    action_manager_ = new ActionManager(this);
}

void CorePlugin::initMainWindow()
{
    main_window_ = new MainWindow();
}

void CorePlugin::initViewSystem()
{
    view_manager_ = new ViewSystem::ViewManager{this};

    ConsoleDockWidget *output_dock_widget = new ConsoleDockWidget{main_window_};
    output_dock_widget->hide();
    DockView *output_dock_view = new DockView();
    output_dock_view->setDockWidget(output_dock_widget);
    output_dock_view->setInitDockLocation(output_dock_widget->DockLocation());

    ViewSpec *output_view_spec = new ViewSpec();
    initViewSpec(output_view_spec, output_dock_widget);
    output_view_spec->setView(output_dock_view);

    ViewManager::addView(output_view_spec);
    PluginManager::addObject(output_dock_view);
}

void CorePlugin::initProgressSystem()
{
    ProgressDockWidget *progress_dock_widget = new ProgressDockWidget{main_window_};
    progress_dock_widget->hide();
    DockView *progress_dock_view = new DockView();
    progress_dock_view->setDockWidget(progress_dock_widget);
    progress_dock_view->setInitDockLocation(progress_dock_widget->DockLocation());

    ViewSpec *progress_view_spec = new ViewSpec();
    initViewSpec(progress_view_spec, progress_dock_widget);
    progress_view_spec->setView(progress_dock_view);

    ViewManager::addView(progress_view_spec);
    PluginManager::addObject(progress_dock_view);

    progress_manager_ = new ProgressManager{this};
    progress_manager_->setProgressView(progress_dock_widget->progressView());
}

void CorePlugin::initViewSpec(ViewSpec *view_spec, ViewSystem::DockWidget *dock_widget)
{
    view_spec->setId(dock_widget->Id());
    view_spec->setName(dock_widget->Name());
    view_spec->setPathList(dock_widget->PathList());
    view_spec->setPluginSpec(this->pluginSpec());
    view_spec->setIconLocation(dock_widget->IconLocation());
}
