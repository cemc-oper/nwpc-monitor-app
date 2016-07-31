#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

#include "loadleveler_monitor_plugin.h"
#include "loadleveler_client.h"

#include "loadleveler_model/job_query_model.h"
#include "loadleveler_model/job_query_item.h"

#include <QMap>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::LoadLevelerModel;

LoadLevelerMonitorWidget::LoadLevelerMonitorWidget(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::LoadLevelerMonitorWidget},
    job_query_model_{nullptr}
{
    ui->setupUi(this);


}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
    if(job_query_model_){
        job_query_model_->deleteLater();
    }
}

void LoadLevelerMonitorWidget::setJobQueryModel(QPointer<JobQueryModel> job_query_model)
{
    if(job_query_model_)
    {
        ui->llq_table_view->setModel(0);
        job_query_model_->deleteLater();
    }
    job_query_model_ = job_query_model;
    ui->llq_table_view->setModel(job_query_model_);
}

void LoadLevelerMonitorWidget::on_query_button_clicked()
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
