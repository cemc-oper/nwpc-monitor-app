#include <loadleveler_monitor/model/query_model.h>
#include <loadleveler_monitor/model/llq_command_manager.h>
#include <loadleveler_monitor/organize_system/filter.h>
#include <loadleveler_monitor/organize_system/filter_value_checker.h>
#include <loadleveler_monitor/organize_system/filter_value_extractor.h>
#include <loadleveler_monitor/organize_system/filter_query_model.h>

#include <QString>
#include <QStringList>
#include <QtTest>

#include <memory>

Q_DECLARE_METATYPE(std::shared_ptr<LoadLevelerMonitor::OrganizeSystem::Filter>)

using namespace std;
using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::OrganizeSystem;

class FilterQueryModelTest : public QObject
{
    Q_OBJECT

public:
    FilterQueryModelTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testFilter_data();
    void testFilter();
private:
    QPointer<LlqCommandManager> manager_;
    QPointer<QueryModel> model_;
};

FilterQueryModelTest::FilterQueryModelTest():
    manager_{new LlqCommandManager}
{
}

void FilterQueryModelTest::initTestCase()
{
    LlqCommandManager::initialize();

    QStringList output{
        "Id                       Owner      Submitted   ST PRI Class        Running On ",
        "------------------------ ---------- ----------- -- --- ------------ -----------",
        "cma20n02.3239038.0       nwp        10/1  00:00 R  100 serial       cma19n05   ",
        "cma20n04.3240584.0       nwp_qu     10/1  00:00 R  100 normal       cma19n06   ",
        "cma20n02.3239059.0       nwp        10/1  00:01 I  100 serial                  ",
        "cma19n02.3241883.0       nwp_xp     10/2  04:00 R  100 serial       cma20n07   ",
        "cma19n02.3243033.0       pos_xp     10/2  05:25 I  100 normal                  ",
        "cma20n02.3241326.0       vfy_xp     10/2  05:27 R  50  normal       cma18n25   ",
        "cma19n02.3243091.0       wangdp     10/4  05:28 R  50  serial       cma10n10   ",
        "cma20n04.3242832.0       winpop     10/4  05:28 R  50  normal       cma20n10   ",
        "cma20n02.3241383.0       nwp_hb     10/5  05:31 R  100 normal       cma11n28   ",
        "cma20n04.3243333.0       nwp        10/3  06:02 R  100 operation1   cma15n22   ",
        "cma20n02.3241861.0       nwp_qu     10/2  06:02 R  100 operation1   cma02n27   ",
        "cma20n02.3241862.0       nwp_qu     10/6  06:02 I  50  operation1              ",
        "cma20n01.3242327.0       nwp        10/7  06:02 I  50  operation1              ",
        "cma19n04.3243252.0       nwp_qu     10/10 06:02 I  50  normal1                 ",
        "cma19n04.3243253.0       nwp_qu     10/12 06:02 I  50  normal1                 ",
        "",
        "15 job step(s) in queue, 6 waiting, 0 pending, 9 running, 0 held, 0 preempted"
    };

    model_ = QueryModel::buildFromLlqDefaultQueryResponse(output);
}

void FilterQueryModelTest::cleanupTestCase()
{
    model_->deleteLater();
    manager_->deleteLater();
}

void FilterQueryModelTest::testFilter_data()
{
    QTest::addColumn<shared_ptr<Filter>>("filter");
    QTest::addColumn<QStringList>("id_list");

    // checker
    auto owner_checker = make_shared<StringChecker>();
    owner_checker->setCondition(StringChecker::OperatorType::Equal, "nwp");

    auto pri_checker = make_shared<NumberChecker>();
    pri_checker->setCondition(NumberChecker::OperatorType::GreaterThan, 50);

    // extractor
    auto owner_extractor = make_shared<QueryCategoryValueExtractor>();
    owner_extractor->setQueryCategory(LlqCommandManager::defaultCategoryList().categoryFromId(Constant::Llq::Owner));

    auto pri_extractor = make_shared<QueryCategoryValueExtractor>();
    pri_extractor->setQueryCategory(LlqCommandManager::defaultCategoryList().categoryFromId(Constant::Llq::Priority));

    // condition
    auto owner_condition = make_shared<FilterCondition>();
    owner_condition->setValueChecker(owner_checker);
    owner_condition->setValueExtractor(owner_extractor);

    auto pri_condition = make_shared<FilterCondition>();
    pri_condition->setValueChecker(pri_checker);
    pri_condition->setValueExtractor(pri_extractor);

    auto owner_filter = make_shared<Filter>();
    owner_filter->setCombinationType(Filter::CombinationType::All);
    owner_filter->addCondition(owner_condition);

    QStringList owner_is_nwp_id_list{
        "cma20n02.3239038.0",
        "cma20n02.3239059.0",
        "cma20n04.3243333.0",
        "cma20n01.3242327.0",
    };

    QTest::newRow("owner_is_nwp")<<owner_filter<<owner_is_nwp_id_list;
}

void FilterQueryModelTest::testFilter()
{
    QFETCH(shared_ptr<Filter>, filter);
    QFETCH(QStringList, id_list);

    auto filter_query_model = make_unique<FilterQueryModel>();
    filter_query_model->setFilter(filter);
    filter_query_model->setSourceModel(model_);

    QCOMPARE(filter_query_model->rowCount(), id_list.size());

    for(int i=0;i<filter_query_model->rowCount();i++)
    {
        QString id = model_->itemFromIndex(filter_query_model->mapToSource(filter_query_model->index(i, 1)))->text();
        QVERIFY(id_list.contains(id));
    }

    for(int i=0; i<id_list.length(); i++)
    {
        QModelIndex index = filter_query_model->index(i, 1);
        QVERIFY(index.isValid());
        QModelIndex source_index = filter_query_model->mapToSource(index);
        QVERIFY(source_index.isValid());
        QStandardItem *item = model_->itemFromIndex(source_index);
        QCOMPARE(item->text(), id_list[i]);
    }
}

QTEST_APPLESS_MAIN(FilterQueryModelTest)

#include "tst_filter_query_model_test.moc"
