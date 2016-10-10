#include <QString>
#include <QtTest>

#include <memory>

#include <loadleveler_monitor/organize_system/filter_value_checker.h>

using namespace LoadLevelerMonitor::OrganizeSystem;

class FilterValueCheckerTest : public QObject
{
    Q_OBJECT

public:
    FilterValueCheckerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testStringChecker_data();
    void testStringChecker();
};

FilterValueCheckerTest::FilterValueCheckerTest()
{
}

void FilterValueCheckerTest::initTestCase()
{
}

void FilterValueCheckerTest::cleanupTestCase()
{
}

void FilterValueCheckerTest::testStringChecker_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<bool>("is_fit");
    QTest::newRow("nwp") << "nwp" << true;
    QTest::newRow("nwp_qu") << "nwp_qu" << true;
    QTest::newRow("nwp_pd") << "nwp_pd" << true;
    QTest::newRow("wangdp") << "wangdp" << false;
}

void FilterValueCheckerTest::testStringChecker()
{
    QFETCH(QString, value);
    QFETCH(bool, is_fit);

    auto checker = std::make_unique<StringChecker>();
    checker->setCondition(StringChecker::OperatorType::Contain, "nwp");

    QCOMPARE(checker->isFit(value), is_fit);

}

QTEST_APPLESS_MAIN(FilterValueCheckerTest)

#include "tst_filter_value_checker_test.moc"
