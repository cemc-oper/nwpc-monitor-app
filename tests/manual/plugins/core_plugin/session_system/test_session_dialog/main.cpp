#include <QApplication>
#include <QPointer>

#include <core_plugin/session_system/session_dialog.h>
#include <core_plugin/session_system/session_manager.h>
#include <core_plugin/session_system/session.h>

#include <QtDebug>

using namespace Core::SessionSystem;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPointer<SessionManager> session_manager = new SessionManager;
    Session wangdp{"wangdp", "uranus.hpc.nmic.cn", "22", "wangdp", "perilla"};
    session_manager->addSession(wangdp);

    SessionDialog session_dialog{session_manager};
    if(session_dialog.exec())
    {
        Session selected_session = session_dialog.getSelectedSession();
        qDebug()<<selected_session.name_;
    }

    return a.exec();
}
