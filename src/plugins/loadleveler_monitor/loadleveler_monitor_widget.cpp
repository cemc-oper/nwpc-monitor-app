#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

#include "loadleveler_monitor_plugin.h"
#include "loadleveler_client.h"

#include <QMap>

using namespace LoadLevelerMonitor;

LoadLevelerMonitorWidget::LoadLevelerMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadLevelerMonitorWidget)
{
    ui->setupUi(this);
}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
}

void LoadLevelerMonitor::LoadLevelerMonitorWidget::on_query_button_clicked()
{
    QMap<QString, QString> args;
    args["host"] = ui->host_edit->text();
    args["port"] = ui->port_edit->text();
    args["user"] = ui->user_edit->text();
    args["password"] = ui->password_edit->text();
    args["command"] = "llq";
    QString arg_string = ui->argument_edit->text();
    if(!arg_string.isEmpty())
        args["command"] += " "+arg_string;

    LoadLevelerMonitorPlugin::client()->runLlqCommand(args);
}
