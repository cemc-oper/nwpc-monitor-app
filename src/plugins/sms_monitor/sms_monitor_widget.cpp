#include "sms_monitor_widget.h"
#include "ui_sms_monitor_widget.h"

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
