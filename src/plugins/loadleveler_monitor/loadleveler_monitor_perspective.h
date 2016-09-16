#pragma once

#include "loadleveler_monitor_global.h"

#include <core_plugin/perspective_system/iperspective.h>

#include <QPointer>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorWidget;

class LOADLEVELER_MONITOR_EXPORT LoadLevelerMonitorPerspective : public Core::PerspectiveSystem::IPerspective
{
    Q_OBJECT
public:
    explicit LoadLevelerMonitorPerspective(QObject *parent = 0);
    ~LoadLevelerMonitorPerspective();

    LoadLevelerMonitorWidget *widget();

private:
    QPointer<LoadLevelerMonitorWidget> loadleveler_monitor_widget_;
};

}
