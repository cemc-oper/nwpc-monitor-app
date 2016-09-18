#include <loadleveler_monitor/model/query_item.h>
#include <loadleveler_monitor/model/query_item_value_saver.h>
#include <loadleveler_monitor/model/special_value_saver.h>

#include <QString>
#include <QtTest>

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
    QTest::addColumn<QVariant>("sort_role");

    // lq
    QTest::newRow("id") << "cma20n02.2871950.0" << "cma20n02.2871950.0" << QVariant("cma20n02.2871950.0");
    QTest::newRow("owner") << "nwp_vfy" <<"nwp_vfy"<< QVariant("nwp_vfy");
    QTest::newRow("class") << "serial" <<"serial" << QVariant("serial");

    // llclass
    QTest::newRow("description") << "" <<"" <<QVariant("");
    QTest::newRow("max_slots") << "9999+" <<"9999+" << QVariant("9999+");
}

void QueryItemValueSaverTest::testString()
{
    QFETCH(QString, value);
    QFETCH(QString, text);
    QFETCH(QVariant, sort_role);

    QueryItemValueSaver *string_saver = new QueryItemStringSaver;
    QueryItem *query_item = new QueryItem;
    string_saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);
    QCOMPARE(string_saver->getItemValue(query_item, QueryItem::SortRole), sort_role);

    delete string_saver;
    delete query_item;
}

void QueryItemValueSaverTest::testNumber_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");
    QTest::addColumn<QVariant>("sort_role");

    QTest::newRow("PRI") << "100" <<"100" << QVariant(100);
}

void QueryItemValueSaverTest::testNumber()
{
    QFETCH(QString, value);
    QFETCH(QString, text);
    QFETCH(QVariant, sort_role);

    QueryItemValueSaver *saver = new QueryItemNumberSaver;
    QueryItem *query_item = new QueryItem;
    saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);
    QCOMPARE(saver->getItemValue(query_item, QueryItem::SortRole), sort_role);

    delete saver;
    delete query_item;
}

void QueryItemValueSaverTest::testDate_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");
    QTest::addColumn<QVariant>("sort_role");

    auto getYear = [](int month){
        QDate cur_date = QDate::currentDate();
        if(month > cur_date.month())
            return cur_date.year() - 1;
        else
            return cur_date.year();
    };

    QDateTime cur_date = QDateTime::currentDateTime();
    cur_date.setTime(QTime(0,0));
    QTest::newRow("0") << "9/7  04:00" <<"09/07 04:00" << QVariant(QDateTime::fromString(QString::number(getYear(9))+"/09/07 04:00", "yyyy/MM/dd hh:mm"));
    QTest::newRow("1") << "9/17 04:02" <<"09/17 04:02" << QVariant(QDateTime::fromString(QString::number(getYear(9))+"/09/17 04:02", "yyyy/MM/dd hh:mm"));
    QTest::newRow("2") << "10/17 04:10" <<"10/17 04:10" << QVariant(QDateTime::fromString(QString::number(getYear(10))+"/10/17 04:10", "yyyy/MM/dd hh:mm"));
}

void QueryItemValueSaverTest::testDate()
{
    QFETCH(QString, value);
    QFETCH(QString, text);
    QFETCH(QVariant, sort_role);

    QueryItemValueSaver *saver = new QueryItemDateSaver;
    QueryItem *query_item = new QueryItem;
    saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);
    QCOMPARE(saver->getItemValue(query_item, QueryItem::SortRole), sort_role);

    delete saver;
    delete query_item;
}

void QueryItemValueSaverTest::testFullDate_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");
    QTest::addColumn<QVariant>("sort_role");

    QTest::newRow("0") << "Wed Sep  7 07:00:02 2016" <<"09/07 07:00" << QVariant(QDateTime::fromString("2016/09/07 07:00:02", "yyyy/MM/dd hh:mm:ss"));
    QTest::newRow("1") << "Tue Aug 23 01:54:30 2016" <<"08/23 01:54" << QVariant(QDateTime::fromString("2016/08/23 01:54:30", "yyyy/MM/dd hh:mm:ss"));
}

void QueryItemValueSaverTest::testFullDate()
{
    QFETCH(QString, value);
    QFETCH(QString, text);
    QFETCH(QVariant, sort_role);

    QueryItemValueSaver *saver = new QueryItemFullDateSaver;
    QueryItem *query_item = new QueryItem;
    saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);
    QCOMPARE(saver->getItemValue(query_item, QueryItem::SortRole), sort_role);

    delete saver;
    delete query_item;
}

void QueryItemValueSaverTest::testJobState_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("text");
    QTest::addColumn<QVariant>("sort_role");

    QTest::newRow("R") << "R" <<"R" << QVariant("R");
    QTest::newRow("Running") << "Running" <<"R" << QVariant("R");
    QTest::newRow("RP") << "RP" <<"RP" << QVariant("RP");
    QTest::newRow("Remove Pending") << "Remove Pending" <<"RP" << QVariant("RP");
}

void QueryItemValueSaverTest::testJobState()
{
    QFETCH(QString, value);
    QFETCH(QString, text);
    QFETCH(QVariant, sort_role);

    QueryItemValueSaver *saver = new JobStateValueSaver;
    QueryItem *query_item = new QueryItem;
    saver->setItemValue(query_item, value);

    QCOMPARE(query_item->text(), text);
    QCOMPARE(saver->getItemValue(query_item, QueryItem::SortRole), sort_role);

    delete saver;
    delete query_item;
}

QTEST_APPLESS_MAIN(QueryItemValueSaverTest)

#include "tst_query_item_value_saver_test.moc"
