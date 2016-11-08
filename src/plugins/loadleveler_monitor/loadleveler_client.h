#pragma once

#include <python_env_plugin/python_engine.h>

#include <QMap>
#include <QPointer>

namespace LoadLevelerMonitor{

class ClientCommandWidget;
namespace Widgets{
class FileViewerWidget;
class JobDetailWidget;
}

namespace Panels{
class LlqPanel;
class QueryPanel;
}

class LoadLevelerClient : public PythonEnv::PythonEngine
{
    Q_OBJECT
public:
    LoadLevelerClient(QObject *parent = 0);
    ~LoadLevelerClient();

    void runLlqCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel = nullptr);
    void runLlcancelCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel = nullptr);
    void runLlholdCommand(QMap<QString, QString> args, QPointer<Panels::LlqPanel> llq_panel = nullptr);
    void runLlclassCommand(QMap<QString, QString> args, QPointer<Panels::QueryPanel> query_panel = nullptr);

    void runCommand(QMap<QString, QString> args, QPointer<ClientCommandWidget> command_widget = nullptr);
    void runFileCommand(QMap<QString, QString> args, QPointer<Widgets::FileViewerWidget> widget = nullptr);

    void runQueryJobDetailCommand(QMap<QString, QString> args, QPointer<Widgets::JobDetailWidget> widget = nullptr);

signals:

public slots:

private:
};

}
