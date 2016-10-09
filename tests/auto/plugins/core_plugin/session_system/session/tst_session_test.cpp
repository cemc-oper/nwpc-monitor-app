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

    void testSessionEmpty();

    void testSession_data();
    void testSession();

    void testLoadSessionFromJson_data();
    void testLoadSessionFromJson();

    void testSessionToArguments_data();
    void testSessionToArguments();
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

void SessionSystemTest::testSessionEmpty()
{
    Session session;
    QVERIFY(session.isEmpty());
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
    QTest::addColumn<QString>("file_path");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("host");
    QTest::addColumn<QString>("port");
    QTest::addColumn<QString>("user");
    QTest::addColumn<QString>("password");

    QString single_session_file_path = QFINDTESTDATA("data/single_session.json");
    QString name, host, port, user, password;
    name = "wangdp@uranus";
    host = "uranus.hpc.nmic.cn";
    port = "22";
    user = "wangdp";
    password = "perilla";

    QTest::newRow("single_session") << single_session_file_path
                                    << name << host << port << user << password;
}

void SessionSystemTest::testLoadSessionFromJson()
{
    QFETCH(QString, file_path);
    QFETCH(QString, name);
    QFETCH(QString, host);
    QFETCH(QString, port);
    QFETCH(QString, user);
    QFETCH(QString, password);

    QFile session_file{file_path};
    QVERIFY2(session_file.open( QIODevice::ReadOnly | QIODevice::Text), "File doesn't exist");

    QJsonDocument doc = QJsonDocument::fromJson(session_file.readAll());
    QVERIFY2(doc.isObject(), "Json file must be an object!");

    QJsonObject object = doc.object();
    Session session{object};

    QCOMPARE(session.name_, name);
    QCOMPARE(session.host_, host);
    QCOMPARE(session.port_, port);
    QCOMPARE(session.user_, user);
    QCOMPARE(session.password_, password);
}

void SessionSystemTest::testSessionToArguments_data()
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

void SessionSystemTest::testSessionToArguments()
{
    QFETCH(QString, name);
    QFETCH(QString, host);
    QFETCH(QString, port);
    QFETCH(QString, user);
    QFETCH(QString, password);

    Session session{name, host, port, user, password};

    QMap<QString, QString> args = session.toArguments();
    QCOMPARE(args["host"], host);
    QCOMPARE(args["port"], port);
    QCOMPARE(args["user"], user);
    QCOMPARE(args["password"], password);
}

QTEST_APPLESS_MAIN(SessionSystemTest)

#include "tst_session_test.moc"
