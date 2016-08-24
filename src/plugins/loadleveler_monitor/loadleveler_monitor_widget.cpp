#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

#include "client_command_widget.h"

#include "loadleveler_model/query_model.h"
#include "loadleveler_model/query_item.h"

#include <QButtonGroup>
#include <QMap>
#include <QMenu>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Model;

LoadLevelerMonitorWidget::LoadLevelerMonitorWidget(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::LoadLevelerMonitorWidget},
    panel_button_group_{new QButtonGroup{this}}
{
    ui->setupUi(this);

    ui->llq_panel->setMonitorWidget(this);

    connect(panel_button_group_, static_cast<void(QButtonGroup::*)(int, bool)>(&QButtonGroup::buttonToggled),
            [=](int id, bool checked){
        if(checked){
            ui->panel_stacked_widget->setCurrentIndex(id);
        }
    });

    panel_button_group_->addButton(ui->llq_panel_button, 0);
    panel_button_group_->addButton(ui->llclass_panel_button, 1);
    panel_button_group_->addButton(ui->llsubmit_panel_button, 2);

    ui->llq_panel_button->setChecked(Qt::Checked);

}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
    if(panel_button_group_){
        panel_button_group_->deleteLater();
    }
}

QMap<QString, QString> LoadLevelerMonitorWidget::getSessionArguments()
{
    QMap<QString, QString> args;
    args["host"] = ui->host_edit->text();
    args["port"] = ui->port_edit->text();
    args["user"] = ui->user_edit->text();
    args["password"] = ui->password_edit->text();
    return args;
}
