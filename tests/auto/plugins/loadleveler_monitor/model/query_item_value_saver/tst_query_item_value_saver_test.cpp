#include <QString>
#include <QtTest>

#include <loadleveler_monitor/model/query_item.h>
#include <loadleveler_monitor/model/query_item_value_saver.h>
#include <loadleveler_monitor/model/special_value_saver.h>

using namespace LoadLevelerMonitor::Model;

class QueryItemValueSaverTest : public QObject
{
    Q_OBJECT

public:
    QueryItemValueSaverTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testString_data();
    void testString();

    void testNumber_data();
    void testNumber();

    void testDate_data();
    void testDate();

    void testFullDate_data();
    void testFullDate();

    void testJobState_data();
    void testJobState();
};

QueryItemValueSaverTest::QueryItemValueSaverTest()
{
}

void QueryItemValueSaverTest::initTestCase()
{
}

void QueryItemValueSaverTest::cleanupTestCase()
{
}

void QueryItemValueSaverTest::testString_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");

    // lq
    QTest::newRow("id") << "cma20n02.2871950.0" <<"cma20n02.2871950.0";
    QTest::newRow("owner") << "nwp_vfy" <<"nwp_vfy";
    QTest::newRow("class") << "serial" <<"serial";

    // llclass
    QTest::newRow("description") << "" <<"";
    QTest::newRow("max_slots") << "9999+" <<"9999+";
}

void QueryItemValueSaverTest::testString()
{
    QFETCH(QString, value);
    QFETCH(QString, text);

    QueryItemValueSaver *string_saver = new QueryItemStringSaver;
    QueryItem *query_item = new QueryItem;
    string_saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);

    delete string_saver;
    delete query_item;
}

void QueryItemValueSaverTest::testNumber_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");

    QTest::newRow("PRI") << "100" <<"100";
}

void QueryItemValueSaverTest::testNumber()
{
    QFETCH(QString, value);
    QFETCH(QString, text);

    QueryItemValueSaver *string_saver = new QueryItemNumberSaver;
    QueryItem *query_item = new QueryItem;
    string_saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);

    delete string_saver;
    delete query_item;
}

void QueryItemValueSaverTest::testDate_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");

    QTest::newRow("0") << "9/7  04:00" <<"09/07 04:00";
    QTest::newRow("1") << "9/17 04:02" <<"09/17 04:02";
    QTest::newRow("2") << "10/17 04:10" <<"10/17 04:10";
}

void QueryItemValueSaverTest::testDate()
{
    QFETCH(QString, value);
    QFETCH(QString, text);

    QueryItemValueSaver *string_saver = new QueryItemDateSaver;
    QueryItem *query_item = new QueryItem;
    string_saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);

    delete string_saver;
    delete query_item;
}

void QueryItemValueSaverTest::testFullDate_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");

    QTest::newRow("0") << "Wed Sep  7 07:00:02 2016" <<"09/07 07:00";
    QTest::newRow("1") << "Tue Aug 23 01:54:30 2016" <<"08/23 01:54";
}

void QueryItemValueSaverTest::testFullDate()
{
    QFETCH(QString, value);
    QFETCH(QString, text);

    QueryItemValueSaver *string_saver = new QueryItemFullDateSaver;
    QueryItem *query_item = new QueryItem;
    string_saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);

    delete string_saver;
    delete query_item;
}

void QueryItemValueSaverTest::testJobState_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");

    QTest::newRow("R") << "R" <<"R";
    QTest::newRow("Running") << "Running" <<"R";
    QTest::newRow("RP") << "RP" <<"RP";
    QTest::newRow("Remove Pending") << "Remove Pending" <<"RP";
}

void QueryItemValueSaverTest::testJobState()
{
    QFETCH(QString, value);
    QFETCH(QString, text);

    QueryItemValueSaver *saver = new JobStateValueSaver;
    QueryItem *query_item = new QueryItem;
    saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);

    delete saver;
    delete query_item;
}

QTEST_APPLESS_MAIN(QueryItemValueSaverTest)

#include "tst_query_item_value_saver_test.moc"
