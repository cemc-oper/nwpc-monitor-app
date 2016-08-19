#pragma once

#include <QWidget>

namespace PythonEnv{
class PythonCommand;
}

namespace LoadLevelerMonitor{

namespace Ui {
class ClientCommandWidget;
}

class ClientCommandWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientCommandWidget(QWidget *parent = 0);
    ~ClientCommandWidget();

    void runPythonCommand(QMap<QString, QString> args);

    void setCommandText(const QString &command);

public slots:
    void receiveResponse(const QString &response);
    void setErrorOutputText(const QString &error_output);
    void setOutputText(const QString &output);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setResponseText(const QString &output);

    Ui::ClientCommandWidget *ui;

    PythonEnv::PythonCommand *python_command_;
};

}
