#pragma once

#include <QWidget>

namespace SmsMonitor{

namespace Ui {
class SmsMonitorWidget;
}

class SmsMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmsMonitorWidget(QWidget *parent = 0);
    ~SmsMonitorWidget();

private:
    Ui::SmsMonitorWidget *ui;
};

}
