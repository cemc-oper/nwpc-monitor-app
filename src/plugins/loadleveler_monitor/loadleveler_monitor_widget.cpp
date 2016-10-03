#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

#include <core_plugin/session_system/session_manager.h>
#include <core_plugin/session_system/session_dialog.h>
#include <plugin_manager/plugin_manager.h>

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
    ui->llclass_panel->setMonitorWidget(this);

    connect(panel_button_group_, static_cast<void(QButtonGroup::*)(int, bool)>(&QButtonGroup::buttonToggled),
            [=](int id, bool checked){
        if(checked){
            ui->panel_stacked_widget->setCurrentIndex(id);
        }
    });

    panel_button_group_->addButton(ui->llq_panel_button, 0);
    panel_button_group_->addButton(ui->llclass_panel_button, 1);
    panel_button_group_->addButton(ui->llsubmit_panel_button, 2);

    ui->llq_panel_button->setChecked(true);

    connect(ui->choose_session_button, &QPushButton::clicked, this, &LoadLevelerMonitorWidget::slotChooseSession);
}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
    if(panel_button_group_){
        panel_button_group_->deleteLater();
    }
}

bool LoadLevelerMonitorWidget::hasSession() const
{
    bool has_empty = ui->host_edit->text().isEmpty()
            || ui->port_edit->text().isEmpty()
            || ui->user_edit->text().isEmpty()
            || ui->password_edit->text().isEmpty();
    return !has_empty;
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

void LoadLevelerMonitorWidget::slotChooseSession()
{
    // NOTE: change way of getting SessionManager.
    QList<Core::SessionSystem::SessionManager *> manager_list = PluginSystem::PluginManager::getObjects<Core::SessionSystem::SessionManager>();
    if(manager_list.length() != 1)
    {
        qWarning()<<"[LoadLevelerMonitorWidget::slotChooseSession] SessionManager must be one. current is "<<manager_list.size();
        return;
    }

    Core::SessionSystem::SessionDialog dialog{manager_list.first(), this};
    if(dialog.exec())
    {
        Core::SessionSystem::Session session = dialog.getSelectedSession();
        setSession(session);
    }

}

void LoadLevelerMonitorWidget::setSession(const Core::SessionSystem::Session &session)
{
    ui->host_edit->setText(session.host_);
    ui->port_edit->setText(session.port_);
    ui->user_edit->setText(session.user_);
    ui->password_edit->setText(session.password_);
}
