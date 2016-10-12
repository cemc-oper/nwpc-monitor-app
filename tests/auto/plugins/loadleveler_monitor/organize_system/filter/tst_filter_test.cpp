#include <loadleveler_monitor/model/query_category_list.h>
#include <loadleveler_monitor/model/query_item.h>

#include <loadleveler_monitor/organize_system/filter.h>
#include <loadleveler_monitor/organize_system/filter_condition.h>
#include <loadleveler_monitor/organize_system/filter_value_checker.h>
#include <loadleveler_monitor/organize_system/filter_value_extractor.h>

#include <QString>
#include <QtTest>

#include <memory>
#include <vector>
#include <tuple>

Q_DECLARE_METATYPE(LoadLevelerMonitor::OrganizeSystem::Filter::CombinationType)
Q_DECLARE_METATYPE(QList<std::shared_ptr<LoadLevelerMonitor::OrganizeSystem::FilterCondition>>)

using namespace std;
using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::OrganizeSystem;

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

private:
    QueryCategoryList llq_default_category_list_;
};

FilterTest::FilterTest()
{
}

void FilterTest::initTestCase()
{
    // repeat is evil
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

void FilterTest::cleanupTestCase()
{
}

void FilterTest::testCategoryFilter_data()
{
    QTest::addColumn<QString>("line");
    QTest::addColumn<QString>("filter_name");
    QTest::addColumn<Filter::CombinationType>("filter_combination_type");
    QTest::addColumn<QList<shared_ptr<FilterCondition>>>("filter_condition_list");
    QTest::addColumn<bool>("is_fit");

    // checker
    auto owner_checker = make_shared<StringChecker>();
    owner_checker->setCondition(StringChecker::OperatorType::StartWith, "nwp");

    auto pri_checker = make_shared<NumberChecker>();
    pri_checker->setCondition(NumberChecker::OperatorType::GreaterThan, 50);

    // extractor
    auto owner_extractor = make_shared<QueryCategoryValueExtractor>();
    owner_extractor->setQueryCategory(llq_default_category_list_.categoryFromId(Constant::Llq::Owner));

    auto pri_extractor = make_shared<QueryCategoryValueExtractor>();
    pri_extractor->setQueryCategory(llq_default_category_list_.categoryFromId(Constant::Llq::Priority));

    // condition
    auto owner_condition = make_shared<FilterCondition>();
    owner_condition->setValueChecker(owner_checker);
    owner_condition->setValueExtractor(owner_extractor);

    auto pri_condition = make_shared<FilterCondition>();
    pri_condition->setValueChecker(pri_checker);
    pri_condition->setValueExtractor(pri_extractor);

    // condition list
    QList<shared_ptr<FilterCondition>> owner_condition_list{owner_condition};
    QList<shared_ptr<FilterCondition>> pri_condition_list{pri_condition};

    // rows
    QTest::newRow("owner.nwp")
            << "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  100 serial       cma20n07   "
            << "owner_belongs_to_nwp"
            << Filter::CombinationType::All
            << owner_condition_list
            << true;

    QTest::newRow("owner.wangdp")
            << "cma20n02.2860805.0       wangdp      9/6  04:00 R  100 serial       cma20n07   "
            << "owner_belongs_to_nwp"
            << Filter::CombinationType::All
            << owner_condition_list
            << false;

    QTest::newRow("pri.100")
            << "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  100 serial       cma20n07   "
            << "pri_greater_than_50"
            << Filter::CombinationType::All
            << pri_condition_list
            << true;

    QTest::newRow("pri.50")
            << "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  50  serial       cma20n07   "
            << "pri_greater_than_50"
            << Filter::CombinationType::All
            << pri_condition_list
            << false;
}

void FilterTest::testCategoryFilter()
{
    QFETCH(QString, line);
    QFETCH(QString, filter_name);
    QFETCH(Filter::CombinationType, filter_combination_type);
    QFETCH(QList<shared_ptr<FilterCondition>>, filter_condition_list);
    QFETCH(bool, is_fit);

    auto row = QueryItem::buildDefaultQueryRow(line, llq_default_category_list_);

    auto filter = make_unique<Filter>();

    filter->setName(filter_name);
    QCOMPARE(filter->name(), filter_name);

    filter->setCombinationType(filter_combination_type);
    QCOMPARE(filter->combinationType(), filter_combination_type);

    foreach(shared_ptr<FilterCondition> filter_condition, filter_condition_list)
    {
        filter->addCondition(filter_condition);
    }

    QCOMPARE(filter->isFit(row), is_fit);
}

QTEST_APPLESS_MAIN(FilterTest)

#include "tst_filter_test.moc"
