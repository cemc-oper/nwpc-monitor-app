#include <loadleveler_monitor/organize_system/filter_value_checker.h>

#include <QString>
#include <QtTest>

#include <memory>

Q_DECLARE_METATYPE(LoadLevelerMonitor::OrganizeSystem::StringChecker::OperatorType)

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
    QTest::addColumn<StringChecker::OperatorType>("type");
    QTest::addColumn<QString>("condition_value");
    QTest::addColumn<bool>("is_fit");

    QTest::newRow("Contain.nwp")    << "nwp"    << StringChecker::OperatorType::Contain << "nwp"    << true;
    QTest::newRow("Contain.nwp_qu") << "nwp_qu" << StringChecker::OperatorType::Contain << "nwp"    << true;
    QTest::newRow("Contain.nwp_sp") << "nwp_sp" << StringChecker::OperatorType::Contain << "wp"     << true;
    QTest::newRow("Contain.wangdp") << "wangdp" << StringChecker::OperatorType::Contain << "nwp"    << false;

    QTest::newRow("Equal.nwp")      << "nwp"    << StringChecker::OperatorType::Equal   << "nwp"    << true;
    QTest::newRow("Equal.nwp_qu")   << "nwp_qu" << StringChecker::OperatorType::Equal   << "nwp"    << false;
    QTest::newRow("Equal.wangdp")   << "wangdp" << StringChecker::OperatorType::Equal   << "nwp"    << false;

    QTest::newRow("StartWith.nwp")      << "nwp"    << StringChecker::OperatorType::StartWith  << "nwp"    << true;
    QTest::newRow("StartWith.nwp_qu")   << "nwp_qu" << StringChecker::OperatorType::StartWith  << "nwp"    << true;
    QTest::newRow("StartWith.wangdp")   << "wangdp" << StringChecker::OperatorType::StartWith  << "nwp"    << false;
    QTest::newRow("StartWith.nwp_sp")   << "nwp_sp" << StringChecker::OperatorType::StartWith  << "sp"    << false;

    QTest::newRow("EndsWith.nwp")      << "nwp"    << StringChecker::OperatorType::EndsWith  << "nwp"    << true;
    QTest::newRow("EndsWith.nwp_qu")   << "nwp_qu" << StringChecker::OperatorType::EndsWith  << "nwp"    << false;
    QTest::newRow("EndsWith.wangdp")   << "wangdp" << StringChecker::OperatorType::EndsWith  << "dp"     << true;
    QTest::newRow("EndsWith.nwp_sp")   << "nwp_sp" << StringChecker::OperatorType::EndsWith  << "wp"     << false;

    QTest::newRow("NotContain.nwp")    << "nwp"    << StringChecker::OperatorType::NotContain << "nwp"    << false;
    QTest::newRow("NotContain.nwp_qu") << "nwp_qu" << StringChecker::OperatorType::NotContain << "nwp"    << false;
    QTest::newRow("NotContain.nwp_sp") << "nwp_sp" << StringChecker::OperatorType::NotContain << "wp"     << false;
    QTest::newRow("NotContain.wangdp") << "wangdp" << StringChecker::OperatorType::NotContain << "nwp"    << true;

    QTest::newRow("RegExp.nwp")    << "nwp"    << StringChecker::OperatorType::RegExp   << "^nwp"    << true;
    QTest::newRow("RegExp.nwp")    << "nwp_qu" << StringChecker::OperatorType::RegExp   << "^nwp"    << true;
    QTest::newRow("RegExp.cma20n03")    << "cma20n03" << StringChecker::OperatorType::RegExp   << "^cma\\d{2}n\\d{2}"    << true;
    QTest::newRow("RegExp.cmb18n03")    << "cmb18n03" << StringChecker::OperatorType::RegExp   << "^cma\\d{2}n\\d{2}"    << false;
}

void FilterValueCheckerTest::testStringChecker()
{
    QFETCH(QString, value);
    QFETCH(StringChecker::OperatorType, type);
    QFETCH(QString, condition_value);
    QFETCH(bool, is_fit);

    auto checker = std::make_unique<StringChecker>();
    checker->setCondition(type, condition_value);

    QCOMPARE(checker->isFit(value), is_fit);

}

QTEST_APPLESS_MAIN(FilterValueCheckerTest)

#include "tst_filter_value_checker_test.moc"
