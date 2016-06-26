#include "core_plugin.h"


CorePlugin::CorePlugin(QObject *parent) :
    QGenericPlugin(parent)
{
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(core_plugin, CorePlugin)
#endif // QT_VERSION < 0x050000
