#include "loadleveler_monitor_perspective.h"

#include "loadleveler_monitor_widget.h"

using namespace LoadLevelerMonitor;
using namespace Core;

LoadLevelerMonitorPerspective::LoadLevelerMonitorPerspective(QObject *parent):
    IPerspective(parent)
{
    setDisplayName("LoadlevelerMonitor");
    setId("loadleveler_monitor");

    loadleveler_monitor_widget_ = new LoadLevelerMonitorWidget();
    setWidget(loadleveler_monitor_widget_);
}

LoadLevelerMonitorPerspective::~LoadLevelerMonitorPerspective()
{
    delete loadleveler_monitor_widget_;
    loadleveler_monitor_widget_ = 0;
}

LoadLevelerMonitorWidget *LoadLevelerMonitorPerspective::widget()
{
    return loadleveler_monitor_widget_;
}
