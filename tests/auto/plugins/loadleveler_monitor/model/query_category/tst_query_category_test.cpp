#include <QString>
#include <QtTest>

#include <loadleveler_monitor/model/query_category.h>

using namespace LoadLevelerMonitor::Model;

class QueryCategoryTest : public QObject
{
    Q_OBJECT

public:
    QueryCategoryTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testGetCategoryColumnWidth_data();
    void testGetCategoryColumnWidth();
};

QueryCategoryTest::QueryCategoryTest()
{
}

void QueryCategoryTest::initTestCase()
{
}

void QueryCategoryTest::cleanupTestCase()
{
}

void QueryCategoryTest::testGetCategoryColumnWidth_data()
{
    QTest::addColumn<QString>("mark_line");
    QTest::addColumn<QVector<int>>("width_vector");
    QTest::newRow("llq")
            << "------------------------ ---------- ----------- -- --- ------------ -----------"
            << QVector<int>{24, 10, 11, 2, 3, 12, 11};
    QTest::newRow("llclass")
            << "--------------- -------------- -------------- ----- ----- ---------------------"
            << QVector<int>{15, 14, 14, 5, 5, 21};
}

void QueryCategoryTest::testGetCategoryColumnWidth()
{
    QFETCH(QString, mark_line);
    QFETCH(QVector<int>, width_vector);
    QVector<int> category_width = getCategoryColumnWidth(mark_line);
    QCOMPARE(category_width.length(), width_vector.length());

    for(int i=0; i<category_width.length(); i++)
    {
        QCOMPARE(category_width[i], width_vector[i]);
    }
}

QTEST_APPLESS_MAIN(QueryCategoryTest)

#include "tst_query_category_test.moc"
