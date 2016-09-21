#include "session_setting_dialog.h"
#include "ui_session_setting_dialog.h"

using namespace Core::SessionSystem;

SessionSettingDialog::SessionSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SessionSettingDialog)
{
    ui->setupUi(this);
}

SessionSettingDialog::~SessionSettingDialog()
{
    delete ui;
}
