#include <QString>
#include <QtTest>
#include <tuple>

#include <loadleveler_monitor/model/query_category.h>

using namespace LoadLevelerMonitor::Model;

class FilterConditionTest : public QObject
{
    Q_OBJECT

public:
    FilterConditionTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testCategoryFilter_data();
    void testCategoryFilter();
};

FilterConditionTest::FilterConditionTest()
{

}

void FilterConditionTest::initTestCase()
{

}

void FilterConditionTest::cleanupTestCase()
{

}

void FilterConditionTest::testCategoryFilter_data()
{
    DefaultQueryCategoryType category_record = std::make_tuple(
                Constant::Llq::Submitted, "Submitted", "Submitted", QueryValueType::Date, "", kQueryTableRecordParser, QVariantList{});
    QueryCategory submit_category = QueryCategoryFactory::createLlqDetialQueryCategory(category_record);
}

void FilterConditionTest::testCategoryFilter()
{
//    QFETCH(QList<QStandardItem*>, model_row);
//    QFETCH(QueryCategory, category);
//    QFETCH(bool, is_fit);

//    CategoryFilterCondition filter;
//    filter.setQueryCategory(category);

//    QCOMPARE(filter.isFit(model_row), is_fit);
}

QTEST_APPLESS_MAIN(FilterConditionTest)

#include "tst_filter_condition_test.moc"
