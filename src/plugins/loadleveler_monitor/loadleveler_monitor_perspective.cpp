#include "loadleveler_monitor_perspective.h"

#include "loadleveler_monitor_widget.h"

using namespace LoadlevelerMonitor;
using namespace Core;

LoadlevelerMonitorPerspective::LoadlevelerMonitorPerspective(QObject *parent):
    IPerspective(parent)
{
    setDisplayName("LoadlevelerMonitor");
    setId("loadleveler_monitor");

    loadleveler_monitor_widget_ = new LoadlevelerMonitorWidget();
    setWidget(loadleveler_monitor_widget_);
}

LoadlevelerMonitorPerspective::~LoadlevelerMonitorPerspective()
{
    delete loadleveler_monitor_widget_;
    loadleveler_monitor_widget_ = 0;
}
