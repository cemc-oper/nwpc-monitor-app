#include "sms_monitor_widget.h"
#include "ui_sms_monitor_widget.h"

#include "sms_monitor_plugin.h"
#include "sms_monitor_client.h"

using namespace SmsMonitor;

SmsMonitorWidget::SmsMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmsMonitorWidget)
{
    ui->setupUi(this);
}

SmsMonitorWidget::~SmsMonitorWidget()
{
    delete ui;
}

void SmsMonitor::SmsMonitorWidget::on_update_sms_staus_button_clicked()
{
    SmsMonitorPlugin::client()->updateStatus();
}
