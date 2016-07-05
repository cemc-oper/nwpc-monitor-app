#pragma once

#include "sms_monitor_global.h"

#include <core_plugin/iperspective.h>

namespace SmsMonitor{

class SmsMonitorWidget;

class SMS_MONITOR_EXPORT SmsMonitorPerspective : public Core::IPerspective
{
    Q_OBJECT
public:
    explicit SmsMonitorPerspective(QObject *parent = 0);

    ~SmsMonitorPerspective();

private:
    SmsMonitorWidget* sms_monitor_widget_;
};

}
