#pragma once

#include "loadleveler_monitor_global.h"

#include <core_plugin/iperspective.h>

namespace LoadlevelerMonitor{

class LoadlevelerMonitorWidget;

class LOADLEVELER_MONITOR_EXPORT LoadlevelerMonitorPerspective : public Core::IPerspective
{
    Q_OBJECT
public:
    explicit LoadlevelerMonitorPerspective(QObject *parent = 0);

    ~LoadlevelerMonitorPerspective();

private:
    LoadlevelerMonitorWidget* loadleveler_monitor_widget_;
};

}
