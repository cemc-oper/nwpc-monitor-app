#pragma once

#include "sms_monitor_global.h"

#include <core_plugin/perspective_system/iperspective.h>

namespace SmsMonitor{

class SmsMonitorWidget;

class SMS_MONITOR_EXPORT SmsMonitorPerspective : public Core::PerspectiveSystem::IPerspective
{
    Q_OBJECT
public:
    explicit SmsMonitorPerspective(QObject *parent = 0);

    ~SmsMonitorPerspective();

    SmsMonitorWidget *widget();

private:
    SmsMonitorWidget* sms_monitor_widget_;
};

}
