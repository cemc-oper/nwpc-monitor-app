#pragma once
#include "../loadleveler_monitor_global.h"

#include <QString>

namespace LoadLevelerMonitor{

namespace Model{

namespace QueryUtil{

LOADLEVELER_MONITOR_EXPORT bool isDetailQuery(const QString &command, const QStringList &arguments);

}
}
}
