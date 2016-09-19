#include <QString>
#include <QtTest>
#include <QCoreApplication>

class SessionWidgetTest : public QObject
{
    Q_OBJECT

public:
    SessionWidgetTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
};

SessionWidgetTest::SessionWidgetTest()
{
}

void SessionWidgetTest::initTestCase()
{
}

void SessionWidgetTest::cleanupTestCase()
{
}

void SessionWidgetTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void SessionWidgetTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(SessionWidgetTest)

#include "tst_session_widget_test.moc"
