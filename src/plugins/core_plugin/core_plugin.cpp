#include "core_plugin.h"

#include "mainwindow.h"
#include "action_system/action_manager.h"
#include "view_system/view_manager.h"
#include "views/output_dock_widget.h"
#include "view_system/view_spec.h"
#include "view_system/dock_view.h"

#include <plugin_manager/plugin_manager.h>

using namespace Core;
using namespace PluginSystem;
using namespace Core::Views;
using namespace Core::ViewSystem;

CorePlugin::CorePlugin(QObject *parent) :
    IPlugin(parent),
    main_window_(nullptr),
    action_manager_{nullptr},
    view_manager_{nullptr}
{
}

CorePlugin::~CorePlugin()
{
    delete main_window_;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *error_string)
{
    action_manager_ = new ActionManager(this);
    view_manager_ = new ViewSystem::ViewManager(this);
    main_window_ = new MainWindow();

    initViews();

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

void CorePlugin::initViews()
{
    OutputDockWidget *output_dock_widget = new OutputDockWidget{main_window_};
    output_dock_widget->hide();
    DockView *output_dock_view = new DockView();
    output_dock_view->setDockWidget(output_dock_widget);
    output_dock_view->setInitDockLocation(output_dock_widget->DockLocation);

    ViewSpec *output_view_spec = new ViewSpec();
    output_view_spec->setId(output_dock_widget->Id);
    output_view_spec->setName(output_dock_widget->Name);
    output_view_spec->setPathList(output_dock_widget->PathList);
    output_view_spec->setPluginSpec(this->pluginSpec());
    output_view_spec->setView(output_dock_view);

    ViewManager::addView(output_view_spec);
    PluginManager::addObject(output_dock_view);
}
