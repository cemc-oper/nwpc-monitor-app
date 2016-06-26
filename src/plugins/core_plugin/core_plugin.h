#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

#include <QGenericPlugin>

#include <plugin_manager/plugin_manager.h>


class CorePlugin : public QGenericPlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "core_plugin.json")
#endif // QT_VERSION >= 0x050000

public:
    CorePlugin(QObject *parent = 0);
};

#endif // CORE_PLUGIN_H
