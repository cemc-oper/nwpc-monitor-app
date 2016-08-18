#pragma once

#include <QWidget>

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

    void setCommandText(const QString &command);

    void receiveResponse(const QString &response);

    void setOutputText(const QString &output);
    void setErrorOutputText(const QString &error_output);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setResponseText(const QString &output);

    Ui::ClientCommandWidget *ui;
};

}
