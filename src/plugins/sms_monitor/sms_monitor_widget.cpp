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

void SmsMonitorWidget::showMessageOnMessagePanel(const QString &message)
{
    QString text = ui->message_text_edit->toPlainText();
    ui->message_text_edit->setPlainText(text+"\n"+message);
}

void SmsMonitor::SmsMonitorWidget::on_update_sms_staus_button_clicked()
{
    SmsMonitorPlugin::client()->updateStatus();
}
