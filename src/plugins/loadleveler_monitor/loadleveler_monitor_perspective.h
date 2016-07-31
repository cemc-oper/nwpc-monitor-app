#pragma once

#include "loadleveler_monitor_global.h"

#include <core_plugin/iperspective.h>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorWidget;

class LOADLEVELER_MONITOR_EXPORT LoadLevelerMonitorPerspective : public Core::IPerspective
{
    Q_OBJECT
public:
    explicit LoadLevelerMonitorPerspective(QObject *parent = 0);

    ~LoadLevelerMonitorPerspective();

    LoadLevelerMonitorWidget *widget();

private:
    LoadLevelerMonitorWidget* loadleveler_monitor_widget_;
};

}
