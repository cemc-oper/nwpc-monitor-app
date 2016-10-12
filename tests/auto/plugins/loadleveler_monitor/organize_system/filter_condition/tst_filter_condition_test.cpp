#include <loadleveler_monitor/model/query_category.h>
#include <loadleveler_monitor/model/query_category_list.h>
#include <loadleveler_monitor/model/query_item.h>
#include <loadleveler_monitor/model/query_model.h>

#include <loadleveler_monitor/organize_system/filter_value_checker.h>
#include <loadleveler_monitor/organize_system/filter_value_extractor.h>
#include <loadleveler_monitor/organize_system/filter_condition.h>

#include <QString>
#include <QtTest>

#include <memory>
#include <vector>
#include <tuple>

Q_DECLARE_METATYPE(LoadLevelerMonitor::Model::QueryCategory)
Q_DECLARE_METATYPE(std::shared_ptr<LoadLevelerMonitor::OrganizeSystem::FilterValueChecker>)
Q_DECLARE_METATYPE(std::shared_ptr<LoadLevelerMonitor::OrganizeSystem::FilterValueExtractor>)

using namespace std;
using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::OrganizeSystem;

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

private:
    QueryCategoryList llq_default_category_list_;
};

FilterConditionTest::FilterConditionTest()
{
}

void FilterConditionTest::initTestCase()
{
    //TODO: repeat is evil
    QString llq_category_mark_line = "------------------------ ---------- ----------- -- --- ------------ -----------";
    QVector<int> llq_category_column_width = getCategoryColumnWidth(llq_category_mark_line);

    vector<tuple<QString, QString, QueryValueType, int>> llq_default_vector = {
        make_tuple(Constant::Llq::Id,           "Id",           QueryValueType::String, llq_category_column_width[0]),
        make_tuple(Constant::Llq::Owner,        "Owner",        QueryValueType::String, llq_category_column_width[1]),
        make_tuple(Constant::Llq::Submitted,    "Submiited",    QueryValueType::Date,   llq_category_column_width[2]),
        make_tuple(Constant::Llq::Status,       "ST",           QueryValueType::String, llq_category_column_width[3]),
        make_tuple(Constant::Llq::Priority,     "PRI",          QueryValueType::Number, llq_category_column_width[4]),
        make_tuple(Constant::Llq::Class,        "Class",        QueryValueType::String, llq_category_column_width[5]),
        make_tuple(Constant::Llq::HostName,     "Running On",   QueryValueType::String, llq_category_column_width[6]),
    };

    int pos = 0;
    for_each(llq_default_vector.begin(), llq_default_vector.end(),
             [&pos, this](const auto &t){
        QueryCategory c;
        c.id_ = get<0>(t);
        c.label_ = get<1>(t);
        c.value_saver_ = QueryItemValueSaverFactory::make(get<2>(t));
        QVariantList args;
        args<< pos << pos + get<3>(t);
        c.record_parser_.reset(QueryRecordParserFactory::make(
                                  kQueryTableRecordParser, args));
        llq_default_category_list_.append(c);

        pos += get<3>(t) + 1;
    });

}

void FilterConditionTest::cleanupTestCase()
{

}

void FilterConditionTest::testCategoryFilter_data()
{
    QTest::addColumn<QString>("line");
    QTest::addColumn<shared_ptr<FilterValueChecker>>("value_checker");
    QTest::addColumn<shared_ptr<FilterValueExtractor>>("value_extractor");
    QTest::addColumn<bool>("is_fit");


    auto string_checker = make_shared<StringChecker>();
    string_checker->setCondition(StringChecker::OperatorType::StartWith, "nwp");

    auto category_extractor = make_shared<QueryCategoryValueExtractor>();
    category_extractor->setQueryCategory(llq_default_category_list_.categoryFromId(Constant::Llq::Owner));

    QTest::newRow("string")
            << "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  100 serial       cma20n07   "
            << static_cast<shared_ptr<FilterValueChecker>>(string_checker)
            << static_cast<shared_ptr<FilterValueExtractor>>(category_extractor)
            << true;


//    QTest::newRow("number")
//        << "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  100 serial       cma20n07   "
//        << llq_default_category_list_.categoryFromId(Constant::Llq::Priority)
//        << QVariant{100};

//    QDate cur_date = QDate::currentDate();
//    int year = cur_date.year();
//    if(cur_date.month() < 9)
//        year -= 1;

//    QTest::newRow("date")
//        << "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  100 serial       cma20n07   "
//        << llq_default_category_list_.categoryFromId(Constant::Llq::Submitted)
//        << QVariant{QDateTime{QDate{year, 9, 6}, QTime{4,0}}};

//    QTest::newRow("empty string")
//        << "cma20n04.2865560.0       nwp_sp     11/16 07:58 I  100 serial                  "
//        << llq_default_category_list_.categoryFromId(Constant::Llq::HostName)
//        << QVariant{""};
}

void FilterConditionTest::testCategoryFilter()
{
    QFETCH(QString, line);

    QFETCH(shared_ptr<FilterValueChecker>, value_checker);
    QFETCH(shared_ptr<FilterValueExtractor>, value_extractor);

    QFETCH(bool, is_fit);

    QList<QueryItem *> row = QueryItem::buildDefaultQueryRow(line, llq_default_category_list_);

    auto filter = make_unique<FilterCondition>();

    filter->setValueExtractor(value_extractor);
    filter->setValueChecker(value_checker);

    QCOMPARE(filter->isFit(row), is_fit);
}

QTEST_APPLESS_MAIN(FilterConditionTest)

#include "tst_filter_condition_test.moc"
