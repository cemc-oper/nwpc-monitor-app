#pragma once

#include "sms_model/bunch.h"

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

    void setBunch(SmsModel::Bunch *bunch);

    void showMessageOnMessagePanel(const QString &message);

private slots:
    void on_update_sms_staus_button_clicked();

private:
    Ui::SmsMonitorWidget *ui;

    SmsModel::Bunch *bunch_;

};

}
