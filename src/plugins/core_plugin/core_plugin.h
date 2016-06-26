#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

#include <QGenericPlugin>

#include <plugin_manager/iplugin.h>


class CorePlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cma.nwpc.nwpc-monitor-app.plugin" FILE "core_plugin.json")

public:
    CorePlugin(QObject *parent = 0);
};

#endif // CORE_PLUGIN_H
