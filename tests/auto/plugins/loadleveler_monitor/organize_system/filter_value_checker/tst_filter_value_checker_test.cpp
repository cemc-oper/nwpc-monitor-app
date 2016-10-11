#include <loadleveler_monitor/organize_system/filter_value_checker.h>

#include <QString>
#include <QDateTime>
#include <QtTest>

#include <memory>

Q_DECLARE_METATYPE(LoadLevelerMonitor::OrganizeSystem::StringChecker::OperatorType)
Q_DECLARE_METATYPE(LoadLevelerMonitor::OrganizeSystem::NumberChecker::OperatorType)
Q_DECLARE_METATYPE(LoadLevelerMonitor::OrganizeSystem::DateTimeChecker::OperatorType)
Q_DECLARE_METATYPE(LoadLevelerMonitor::OrganizeSystem::BooleanChecker::OperatorType)

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

    void testNumberChecker_data();
    void testNumberChecker();

    void testDateTimeChecker_data();
    void testDateTimeChecker();

    void testBooleanChecker_data();
    void testBooleanChecker();
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

void FilterValueCheckerTest::testNumberChecker_data()
{
    QTest::addColumn<int>("value");
    QTest::addColumn<NumberChecker::OperatorType>("type");
    QTest::addColumn<int>("condition_value");
    QTest::addColumn<bool>("is_fit");

    QTest::newRow("GreaterThan.1")    << 10 << NumberChecker::OperatorType::GreaterThan   << 5    << true;
    QTest::newRow("GreaterThan.2")    << 10 << NumberChecker::OperatorType::GreaterThan   << 10   << false;
    QTest::newRow("GreaterThan.3")    << 10 << NumberChecker::OperatorType::GreaterThan   << 15   << false;

    QTest::newRow("Equal.1")          << 10 << NumberChecker::OperatorType::Equal         << 10   << true;
    QTest::newRow("Equal.2")          << 10 << NumberChecker::OperatorType::Equal         << 11   << false;
    QTest::newRow("Equal.3")          << 10 << NumberChecker::OperatorType::Equal         << 9    << false;

    QTest::newRow("NotEqual.1")       << 10 << NumberChecker::OperatorType::NotEqual      << 10   << false;
    QTest::newRow("NotEqual.2")       << 10 << NumberChecker::OperatorType::NotEqual      << 11   << true;
    QTest::newRow("NotEqual.3")       << 10 << NumberChecker::OperatorType::NotEqual      << 9    << true;

    QTest::newRow("LessThan.1")       << 10 << NumberChecker::OperatorType::LessThan      << 15   << true;
    QTest::newRow("LessThan.2")       << 10 << NumberChecker::OperatorType::LessThan      << 10   << false;
    QTest::newRow("LessThan.3")       << 10 << NumberChecker::OperatorType::LessThan      << 5    << false;

}

void FilterValueCheckerTest::testNumberChecker()
{
    QFETCH(int, value);
    QFETCH(NumberChecker::OperatorType, type);
    QFETCH(int, condition_value);
    QFETCH(bool, is_fit);

    auto checker = std::make_unique<NumberChecker>();
    checker->setCondition(type, condition_value);

    QCOMPARE(checker->isFit(value), is_fit);
}

void FilterValueCheckerTest::testDateTimeChecker_data()
{
    QTest::addColumn<QDateTime>("value");
    QTest::addColumn<DateTimeChecker::OperatorType>("type");
    QTest::addColumn<QDateTime>("condition_value");
    QTest::addColumn<bool>("is_fit");

    QTest::newRow("Before.1") << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::Before
                              << QDateTime{ QDate{2016, 10, 11}, QTime{9, 00, 0} }
                              << true;
    QTest::newRow("Before.2") << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::Before
                              << QDateTime{ QDate{2016, 10, 11}, QTime{7, 0, 0} }
                              << false;
    QTest::newRow("Before.3") << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::Before
                              << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << false;

    QTest::newRow("Equal.1")  << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::Equal
                              << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << true;
    QTest::newRow("Equal.2")  << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::Equal
                              << QDateTime{ QDate{2016, 10, 11}, QTime{9, 0, 0} }
                              << false;

    QTest::newRow("NotEqual.1") << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                                << DateTimeChecker::OperatorType::NotEqual
                                << QDateTime{ QDate{2016, 10, 11}, QTime{9, 0, 0} }
                                << true;
    QTest::newRow("NotEqual.2") << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                                << DateTimeChecker::OperatorType::NotEqual
                                << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                                << false;

    QTest::newRow("After.1")  << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::After
                              << QDateTime{ QDate{2016, 10, 11}, QTime{7, 0, 0} }
                              << true;
    QTest::newRow("After.2")  << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::After
                              << QDateTime{ QDate{2016, 10, 11}, QTime{9, 0, 0} }
                              << false;
    QTest::newRow("After.3")  << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << DateTimeChecker::OperatorType::After
                              << QDateTime{ QDate{2016, 10, 11}, QTime{8, 0, 0} }
                              << false;
}

void FilterValueCheckerTest::testDateTimeChecker()
{
    QFETCH(QDateTime, value);
    QFETCH(DateTimeChecker::OperatorType, type);
    QFETCH(QDateTime, condition_value);
    QFETCH(bool, is_fit);

    auto checker = std::make_unique<DateTimeChecker>();
    checker->setCondition(type, condition_value);

    QCOMPARE(checker->isFit(value), is_fit);
}

void FilterValueCheckerTest::testBooleanChecker_data()
{
    QTest::addColumn<bool>("value");
    QTest::addColumn<BooleanChecker::OperatorType>("type");
    QTest::addColumn<bool>("is_fit");

    QTest::newRow("Set.1")      << true     << BooleanChecker::OperatorType::Set    << true;
    QTest::newRow("Set.2")      << false    << BooleanChecker::OperatorType::Set    << false;
    QTest::newRow("Unset.1")    << true     << BooleanChecker::OperatorType::Unset  << false;
    QTest::newRow("Unset.2")    << false    << BooleanChecker::OperatorType::Unset  << true;
}

void FilterValueCheckerTest::testBooleanChecker()
{
    QFETCH(bool, value);
    QFETCH(BooleanChecker::OperatorType, type);
    QFETCH(bool, is_fit);

    auto checker = std::make_unique<BooleanChecker>();
    checker->setCondition(type);

    QCOMPARE(checker->isFit(value), is_fit);
}

QTEST_APPLESS_MAIN(FilterValueCheckerTest)

#include "tst_filter_value_checker_test.moc"
