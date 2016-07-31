#include "client_command_widget.h"
#include "ui_client_command_widget.h"

#include <QtDebug>

using namespace LoadLevelerMonitor;

ClientCommandWidget::ClientCommandWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientCommandWidget)
{
    ui->setupUi(this);
    ui->message_tab_widget->setCurrentIndex(0);

    //setAttribute(Qt::WA_DeleteOnClose, true);
}

ClientCommandWidget::~ClientCommandWidget()
{
    qDebug()<<"[ClientCommandWidget::~ClientCommandWidget] delete";
    delete ui;
}

void ClientCommandWidget::setOutputText(const QString &output)
{
    ui->output_edit->setText(output);
}

void ClientCommandWidget::setErrorOutputText(const QString &error_output)
{
    ui->error_output_edit->setText(error_output);
}

void ClientCommandWidget::closeEvent(QCloseEvent *event)
{
    qDebug()<<"[ClientCommandWidget::closeEvent] closeEvent";
    this->deleteLater();
}
