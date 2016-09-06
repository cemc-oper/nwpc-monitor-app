#include <QString>
#include <QtTest>

#include <loadleveler_monitor/model/query_util.h>

using namespace LoadLevelerMonitor::Model;

class QueryUtilTest : public QObject
{
    Q_OBJECT

public:
    QueryUtilTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testIsDetailQuery_data();
    void testIsDetailQuery();
};

QueryUtilTest::QueryUtilTest()
{
}

void QueryUtilTest::initTestCase()
{
}

void QueryUtilTest::cleanupTestCase()
{
}

void QueryUtilTest::testIsDetailQuery_data()
{
    QTest::addColumn<QString>("command");
    QTest::addColumn<QStringList>("arguments");
    QTest::addColumn<bool>("is_detail_query");

    QTest::newRow("0") << "llq" << QStringList() << false;
    QTest::newRow("1") << "llq -u nwp" << QStringList() << false;
    QTest::newRow("2") << "llq -u nwp -l" << QStringList() << true;
    QTest::newRow("3") << "llq -l" << QStringList() << true;
    QTest::newRow("4") << "llq -l -u nwp" << QStringList() << true;
    QTest::newRow("5") << "llq -c normal -l -u nwp" << QStringList() << true;
    QTest::newRow("6") << "llclass" << QStringList() << false;
    QTest::newRow("7") << "llclass -l" << QStringList() << true;
    QTest::newRow("8") << "llclass -c normal -l" << QStringList() << true;
    QTest::newRow("9") << "llclass -l -c normal" << QStringList() << true;
    QTest::newRow("10") << "llclass -c normal" << QStringList() << false;
}

void QueryUtilTest::testIsDetailQuery()
{
    QFETCH(QString, command);
    QFETCH(QStringList, arguments);
    QFETCH(bool, is_detail_query);

    QCOMPARE(QueryUtil::isDetailQuery(command, arguments), is_detail_query);
}

QTEST_APPLESS_MAIN(QueryUtilTest)

#include "tst_query_util_test.moc"
