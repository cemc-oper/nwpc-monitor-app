#include <QString>
#include <QtTest>

class FilterTest : public QObject
{
    Q_OBJECT

public:
    FilterTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testCategoryFilter_data();
    void testCategoryFilter();
};

FilterTest::FilterTest()
{
}

void FilterTest::initTestCase()
{
}

void FilterTest::cleanupTestCase()
{
}

void FilterTest::testCategoryFilter_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void FilterTest::testCategoryFilter()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(FilterTest)

#include "tst_filter_test.moc"
