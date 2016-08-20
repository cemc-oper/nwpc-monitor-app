#pragma once

#include <python_env_plugin/python_engine.h>

#include <QMap>
#include <QPointer>

namespace LoadLevelerMonitor{

class ClientCommandWidget;

namespace Panels{
class LlqPanel;
}

class LoadLevelerClient : public PythonEnv::PythonEngine
{
    Q_OBJECT
public:
    LoadLevelerClient(QObject *parent = 0);
    ~LoadLevelerClient();

    void runLlqCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel = nullptr);

    void runCommand(QMap<QString, QString> args, QPointer<ClientCommandWidget> command_widget = nullptr);

signals:

public slots:

private:
};

}
