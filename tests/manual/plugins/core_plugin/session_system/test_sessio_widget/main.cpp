#include <QApplication>
#include <QPointer>

#include <core_plugin/session_system/session_widget.h>
#include <core_plugin/session_system/session_manager.h>


using namespace Core::SessionSystem;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SessionWidget session_widget;

    QPointer<SessionManager> session_manager = new SessionManager;
    session_widget.setSessionManager(session_manager);
    session_widget.show();


    return a.exec();
}
