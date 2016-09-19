#include "session_widget.h"
#include "ui_session_widget.h"

#include "session_manager.h"

using namespace Core::SessionSystem;

SessionWidget::SessionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionWidget)
{
    ui->setupUi(this);
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

void SessionWidget::updateSessionList()
{

}
