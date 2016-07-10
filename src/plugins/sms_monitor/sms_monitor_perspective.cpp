#include "sms_monitor_perspective.h"

#include "sms_monitor_widget.h"

using namespace SmsMonitor;
using namespace Core;

SmsMonitorPerspective::SmsMonitorPerspective(QObject *parent):
    IPerspective(parent)
{
    setDisplayName("SmsMonitor");
    setId("sms_monitor");

    sms_monitor_widget_ = new SmsMonitorWidget();
    setWidget(sms_monitor_widget_);
}

SmsMonitorPerspective::~SmsMonitorPerspective()
{
    delete sms_monitor_widget_;
    sms_monitor_widget_ = 0;
}

SmsMonitorWidget *SmsMonitorPerspective::widget()
{
    return sms_monitor_widget_;
}
