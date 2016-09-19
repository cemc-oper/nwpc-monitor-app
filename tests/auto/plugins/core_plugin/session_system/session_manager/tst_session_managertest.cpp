#include <QString>
#include <QtTest>

#include <core_plugin/session_system/session_manager.h>

using namespace Core::SessionSystem;

class SessionManagerTest : public QObject
{
    Q_OBJECT

public:
    SessionManagerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testAddSession_data();
    void testAddSession();
};

SessionManagerTest::SessionManagerTest()
{
}

void SessionManagerTest::initTestCase()
{

}

void SessionManagerTest::cleanupTestCase()
{
}

void SessionManagerTest::testAddSession_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("host");
    QTest::addColumn<QString>("port");
    QTest::addColumn<QString>("user");
    QTest::addColumn<QString>("password");

    QString name, host, port, user, password;
    name = "wangdp@uranus";
    host = "uranus.hpc.nmic.cn";
    port = "22";
    user = "wangdp";
    password = "perilla";
    QTest::newRow("0") << name << host << port << user << password;
}

void SessionManagerTest::testAddSession()
{
    QFETCH(QString, name);
    QFETCH(QString, host);
    QFETCH(QString, port);
    QFETCH(QString, user);
    QFETCH(QString, password);

    Session session{name, host, port, user, password};

    SessionManager session_manager;
    session_manager.addSession(session);

    QCOMPARE(session_manager.sessionCount(), 1);

    Session first_session = session_manager.getSession(name);
    QCOMPARE(first_session, session);

    auto session_map = session_manager.sessionMap();
    QVERIFY(session_map.contains(name));
    QCOMPARE(session_map.size(), 1);
    QCOMPARE(session_map[name], session);

    session_manager.removeSession(name);
    QCOMPARE(session_manager.sessionCount(), 0);
}

QTEST_APPLESS_MAIN(SessionManagerTest)

#include "tst_session_managertest.moc"
