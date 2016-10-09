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
using namespace Core::SessionSystem;
using namespace PluginSystem;

LoadLevelerMonitorWidget::LoadLevelerMonitorWidget(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::LoadLevelerMonitorWidget},
    panel_button_group_{new QButtonGroup{this}}
{
    ui->setupUi(this);

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

    connect(ui->host_edit, &QLineEdit::editingFinished, this, &LoadLevelerMonitorWidget::slotSessionEditorsChanged);
    connect(ui->port_edit, &QLineEdit::editingFinished, this, &LoadLevelerMonitorWidget::slotSessionEditorsChanged);
    connect(ui->user_edit, &QLineEdit::editingFinished, this, &LoadLevelerMonitorWidget::slotSessionEditorsChanged);
    connect(ui->password_edit, &QLineEdit::editingFinished, this, &LoadLevelerMonitorWidget::slotSessionEditorsChanged);

    connect(ui->choose_session_button, &QPushButton::clicked, this, &LoadLevelerMonitorWidget::slotChooseSession);
}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
    if(panel_button_group_){
        panel_button_group_->deleteLater();
    }
}

void LoadLevelerMonitorWidget::slotChooseSession()
{
    // NOTE: change way of getting SessionManager.
    QList<SessionManager *> manager_list = PluginManager::getObjects<Core::SessionSystem::SessionManager>();
    if(manager_list.length() != 1)
    {
        qWarning()<<"[LoadLevelerMonitorWidget::slotChooseSession] SessionManager must be one. current is "<<manager_list.size();
        return;
    }

    SessionDialog dialog{manager_list.first(), this};
    if(dialog.exec())
    {
        Session session = dialog.getSelectedSession();
        setSession(session);
    }

}

void LoadLevelerMonitorWidget::slotSessionEditorsChanged()
{
    Session session;
    session.host_ = ui->host_edit->text();
    session.port_ = ui->port_edit->text();
    session.user_ = ui->user_edit->text();
    session.password_ = ui->password_edit->text();
    setSessionInQueryPanels(session);
}

void LoadLevelerMonitorWidget::setSession(const Session &session)
{
    ui->host_edit->setText(session.host_);
    ui->port_edit->setText(session.port_);
    ui->user_edit->setText(session.user_);
    ui->password_edit->setText(session.password_);

    setSessionInQueryPanels(session);
}

void LoadLevelerMonitorWidget::setSessionInQueryPanels(const Session &session)
{
    // set session for all query_pages
    ui->llq_panel->setSession(session);
    ui->llclass_panel->setSession(session);
}
