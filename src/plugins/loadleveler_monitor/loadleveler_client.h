#pragma once

#include <python_env_plugin/python_engine.h>

#include <QMap>

namespace LoadLevelerMonitor{

class LoadLevelerClient : public PythonEnv::PythonEngine
{
    Q_OBJECT
public:
    LoadLevelerClient(QObject *parent = 0);
    ~LoadLevelerClient();

    void runLlqCommand(QMap<QString, QString> args);

signals:

public slots:

private:
};

}
