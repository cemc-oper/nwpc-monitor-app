#pragma once

#include "core_plugin_global.h"


#include <plugin_manager/iplugin.h>

class MainWindow;

class CORE_PLUGIN_EXPORT CorePlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "core_plugin.json")

public:
    CorePlugin(QObject *parent = 0);

private:
    MainWindow *mian_window_;
};
