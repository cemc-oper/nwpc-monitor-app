#include "session_widget.h"
#include "ui_session_widget.h"
#include "session_manager.h"
#include "session_setting_dialog.h"

#include <QStandardItemModel>
#include <QStandardItem>

using namespace Core::SessionSystem;

SessionWidget::SessionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionWidget),
    session_model_{new QStandardItemModel{this}}
{
    ui->setupUi(this);

    connect(ui->create_button, &QPushButton::clicked, this, &SessionWidget::createSession);
    connect(ui->edit_button, &QPushButton::clicked, this, &SessionWidget::editSession);
    connect(ui->clone_button, &QPushButton::clicked, this, &SessionWidget::cloneSession);
    connect(ui->remove_button, &QPushButton::clicked, this, &SessionWidget::removeSession);

    ui->session_table_view->setModel(session_model_);
}

SessionWidget::~SessionWidget()
{
    delete ui;
}

void SessionWidget::setSessionManager(SessionManager *manager)
{
    session_manager_ = manager;
    updateSessionList();
}

void SessionWidget::createSession()
{
    SessionSettingDialog setting_dialog{this};
    if(setting_dialog.exec())
    {
        Session *session = setting_dialog.getSession();
        session_manager_->addSession(*session);
    }
    updateSessionList();
}

void SessionWidget::editSession()
{

}

void SessionWidget::removeSession()
{

}

void SessionWidget::cloneSession()
{

}

void SessionWidget::updateSessionList()
{
    session_model_->clear();
    auto session_map = session_manager_->sessionMap();
    QMapIterator<QString, Session> i(session_map);
    while (i.hasNext()) {
        i.next();
        QString id = i.key();
        Session session = i.value();
        session_model_->invisibleRootItem()->appendRow(
            QList<QStandardItem*>()
                    << new QStandardItem{session.name_}
                    << new QStandardItem{session.host_ + ":" + session.port_}
                    << new QStandardItem{session.user_}
        );
    }
    session_model_->setHorizontalHeaderLabels(QStringList()<<"Name"<<"Address"<<"User");
}
