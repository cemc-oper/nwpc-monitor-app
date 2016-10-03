#pragma once

#include "../core_plugin_global.h"
#include "session.h"

#include <QDialog>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

namespace Core{

namespace SessionSystem{

class SessionManager;
class Session;

namespace Ui {
class SessionDialog;
}

class CORE_PLUGIN_EXPORT SessionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionDialog(SessionManager *manager, QWidget *parent = 0);
    ~SessionDialog();

    Session getSelectedSession() const;

public slots:
    void createSession();
    void editSession();
    void removeSession();
    void cloneSession();

protected:
    void accept() override;

private:
    explicit SessionDialog(QWidget *parent = 0);
    void setSessionManager(SessionManager *manager);

    void updateSessionList();
    bool checkSelectedSession();

    Ui::SessionDialog *ui;
    QPointer<SessionManager> session_manager_;
    QPointer<QStandardItemModel> session_model_;

    Session selected_session_;
};

}

}
