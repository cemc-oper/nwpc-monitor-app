#pragma once

#include <python_env_plugin/python_engine.h>

namespace SmsMonitor{

class SmsMonitorClient : public PythonEnv::PythonEngine
{
    Q_OBJECT
public:
    SmsMonitorClient(QObject *parent = 0);
    ~SmsMonitorClient();

    SmsMonitorClient *instance();

    void updateStatus();

signals:

public slots:

private:

};

}
