#include <QString>
#include <QtTest>
#include <QJsonDocument>

#include <core_plugin/session_system/session.h>

using namespace Core::SessionSystem;

class SessionSystemTest : public QObject
{
    Q_OBJECT

public:
    SessionSystemTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testSession_data();
    void testSession();

    void testLoadSessionFromJson_data();
    void testLoadSessionFromJson();
};

SessionSystemTest::SessionSystemTest()
{
}

void SessionSystemTest::initTestCase()
{
}

void SessionSystemTest::cleanupTestCase()
{
}

void SessionSystemTest::testSession_data()
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

void SessionSystemTest::testSession()
{
    QFETCH(QString, name);
    QFETCH(QString, host);
    QFETCH(QString, port);
    QFETCH(QString, user);
    QFETCH(QString, password);

    Session session{name, host, port, user, password};

    QCOMPARE(session.name_, name);
    QCOMPARE(session.host_, host);
    QCOMPARE(session.port_, port);
    QCOMPARE(session.user_, user);
    QCOMPARE(session.password_, password);
}

void SessionSystemTest::testLoadSessionFromJson_data()
{
//    QString single_session_file_path = QFINDTESTDATA("data/single_session.json");
//    QFile single_session_file{single_session_file_path};
//    if(single_session_file.open( QIODevice::ReadOnly | QIODevice::Text))
//    {
//        QJsonDocument doc{single_session_file.readAll()};
//    }
}

void SessionSystemTest::testLoadSessionFromJson()
{

}

QTEST_APPLESS_MAIN(SessionSystemTest)

#include "tst_session_system_test.moc"
