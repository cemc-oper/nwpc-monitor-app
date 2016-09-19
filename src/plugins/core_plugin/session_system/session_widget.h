#pragma once

#include <QWidget>
#include <QPointer>

namespace Core{

namespace SessionSystem{

class SessionManager;

namespace Ui {
class SessionWidget;
}

class SessionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWidget(QWidget *parent = 0);
    ~SessionWidget();

    void setSessionManager(SessionManager *manager);

public slots:
    void createSession();
    void editSession();
    void removeSession();
    void cloneSession();

private:
    void updateSessionList();

    Ui::SessionWidget *ui;
    QPointer<SessionManager> session_manager_;
};

}

}
