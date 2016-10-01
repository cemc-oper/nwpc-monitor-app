#include "session_setting_dialog.h"
#include "ui_session_setting_dialog.h"

#include "session.h"

using namespace Core::SessionSystem;

SessionSettingDialog::SessionSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SessionSettingDialog),
    session_{nullptr}
{
    ui->setupUi(this);
}

SessionSettingDialog::~SessionSettingDialog()
{
    delete ui;
}

void SessionSettingDialog::setSession(Session *session)
{
    session_ = session;
    updateUi();
}

Session *SessionSettingDialog::getSession() const
{
    return session_;
}

void SessionSettingDialog::accept()
{
    if(!session_)
        createSession();
    updateSession();
    return QDialog::accept();
}

void SessionSettingDialog::createSession()
{
    session_ = new Session;
}

void SessionSettingDialog::updateSession()
{
    session_->name_ = ui->name_line_edit->text();
    session_->host_ = ui->host_line_edit->text();
    session_->port_ = ui->port_line_edit->text();
    session_->user_ = ui->user_line_edit->text();
    session_->password_ = ui->password_line_edit->text();
}

void SessionSettingDialog::updateUi()
{
    ui->name_line_edit->setText(session_->name_);
    ui->host_line_edit->setText(session_->host_);
    ui->port_line_edit->setText(session_->port_);
    ui->user_line_edit->setText(session_->user_);
    ui->password_line_edit->setText(session_->password_);
}
