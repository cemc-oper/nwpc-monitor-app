#include "sms_monitor_widget.h"
#include "ui_sms_monitor_widget.h"

#include "sms_monitor_plugin.h"
#include "sms_monitor_client.h"

using namespace SmsMonitor;

SmsMonitorWidget::SmsMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui{new Ui::SmsMonitorWidget},
    bunch_{nullptr}
{
    ui->setupUi(this);

    ui->middle_splitter->setStretchFactor(0,1);
    ui->middle_splitter->setStretchFactor(1,3);

    ui->bottom_splitter->setStretchFactor(0, 5);
    ui->bottom_splitter->setStretchFactor(0, 1);
}

SmsMonitorWidget::~SmsMonitorWidget()
{
    delete ui;
    if(bunch_)
    {
        bunch_->deleteLater();
    }

}

void SmsMonitorWidget::setBunch(QPointer<SmsModel::Bunch> bunch)
{
    if(bunch_)
    {
        ui->bunch_view->setModel(0);
        bunch_->deleteLater();
    }

    bunch_ = bunch;
    ui->bunch_view->setModel(bunch_);
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
