#pragma once

#include <QDialog>
#include <QSharedPointer>

namespace Core{

namespace SessionSystem{

class Session;

namespace Ui {
class SessionSettingDialog;
}

class SessionSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionSettingDialog(QWidget *parent = 0);
    ~SessionSettingDialog();

    void setSession(Session *session);
    Session *getSession() const;

public slots:
    void accept();

private:
    void createSession();
    void updateSession();

    Ui::SessionSettingDialog *ui;
    Session *session_;
};

}

}
