#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QVector>

#include <core_plugin/session_system/session_widget.h>
#include <core_plugin/session_system/session_manager.h>
#include <core_plugin/session_system/session.h>

using namespace Core::SessionSystem;

class SessionWidgetTest : public QObject
{
    Q_OBJECT

public:
    SessionWidgetTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testSetSessionManager();

    void testRemoveSession();

private:
    QVector<Session> session_list_;
};

SessionWidgetTest::SessionWidgetTest()
{
}

void SessionWidgetTest::initTestCase()
{
    QString name, host, port, user, password;
    name = "wangdp@uranus";
    host = "uranus.hpc.nmic.cn";
    port = "22";
    user = "wangdp";
    password = "wangdp_password";
    Session session_one{name, host, port, user, password};
    session_list_.push_back(session_one);

    name = "nwp@uranus";
    host = "uranus-bk.hpc.nmic.cn";
    port = "22";
    user = "nwp";
    password = "nwp_password";
    Session session_two{name, host, port, user, password};
    session_list_.push_back(session_two);
}

void SessionWidgetTest::cleanupTestCase()
{
    session_list_.clear();
}


void SessionWidgetTest::testSetSessionManager()
{
    QPointer<SessionManager> manager = new SessionManager;
    foreach(Session session, session_list_)
    {
        manager->addSession(session);
    }

    QPointer<SessionWidget> session_widget = new SessionWidget;
    session_widget->setSessionManager(manager);

    session_widget->deleteLater();
    manager->deleteLater();
}

QTEST_MAIN(SessionWidgetTest)

#include "tst_session_widget_test.moc"
