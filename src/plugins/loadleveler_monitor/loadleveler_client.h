#pragma once

#include <python_env_plugin/python_engine.h>

namespace LoadLevelerMonitor{

class LoadLevelerClient : public PythonEnv::PythonEngine
{
    Q_OBJECT
public:
    LoadLevelerClient(QObject *parent = 0);
    ~LoadLevelerClient();

    void runLlqCommand();

signals:

public slots:

private:
};

}
