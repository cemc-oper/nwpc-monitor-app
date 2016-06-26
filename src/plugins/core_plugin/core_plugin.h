#pragma once

#include "core_plugin_global.h"


#include <plugin_manager/iplugin.h>

class MainWindow;

class CorePlugin : public IPlugin
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
};
