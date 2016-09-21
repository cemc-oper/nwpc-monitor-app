#include "session_widget.h"
#include "ui_session_widget.h"
#include "session_manager.h"

#include <QStandardItemModel>

using namespace Core::SessionSystem;

SessionWidget::SessionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionWidget)
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

}
