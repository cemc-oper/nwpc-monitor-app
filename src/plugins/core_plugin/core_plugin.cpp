#include "core_plugin.h"

#include "mainwindow.h"

#include <plugin_manager/plugin_manager.h>

using namespace Core;
using namespace PluginSystem;

CorePlugin::CorePlugin(QObject *parent) :
    IPlugin(parent),
    main_window_(0)
{
}

CorePlugin::~CorePlugin()
{
    delete main_window_;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *error_string)
{
    main_window_ = new MainWindow();

    return true;
}

void CorePlugin::pluginsInitialized()
{
    main_window_->loadPerspectives();

    main_window_->activatePerspective("welcome");

    main_window_->show();
}

void CorePlugin::aboutToShutDown()
{
    main_window_->hide();
}
