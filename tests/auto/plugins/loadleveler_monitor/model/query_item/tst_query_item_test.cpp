#include <QString>
#include <QtTest>
#include <QPointer>
#include <QVector>

#include <loadleveler_monitor/model/query_item.h>

#include <algorithm>

using namespace LoadLevelerMonitor::Model;
using namespace std;

class QueryItemTest : public QObject
{
    Q_OBJECT

public:
    QueryItemTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testBuildLlqDefaultQueryRow_data();
    void testBuildLlqDefaultQueryRow();

    void testBuildLlclassDefaultQueryRow_data();
    void testBuildLlclassDefaultQueryRow();

private:
    QueryCategoryList llq_default_category_list_;
    QueryCategoryList llq_detail_category_list_;
    QueryCategoryList llclass_default_category_list_;
    QueryCategoryList llclass_detail_category_list_;
};

QueryItemTest::QueryItemTest()
{
}

void QueryItemTest::initTestCase()
{
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

    for_each(llq_default_vector.begin(), llq_default_vector.end(),
             [=](const auto &t){
        QueryCategory c;
        c.id_ = get<0>(t);
        c.label_ = get<1>(t);
        c.value_type_ = get<2>(t);
        c.token_length_ = get<3>(t);
        llq_default_category_list_.append(c);
    });
}

void QueryItemTest::cleanupTestCase()
{

}

void QueryItemTest::testBuildLlqDefaultQueryRow_data()
{
    QTest::addColumn<QString>("line");
    QTest::addColumn<QString>("id");
    QTest::addColumn<QString>("owner");
    QTest::addColumn<QString>("submitted");
    QTest::addColumn<QString>("status");
    QTest::addColumn<QString>("pri");
    QTest::addColumn<QString>("ll_class");
    QTest::addColumn<QString>("running_on");

    int row_no = 0;
    QStringList lines{
        "cma20n02.2860805.0       nwp_vfy     9/6  04:00 R  100 serial       cma20n07   ",
        "cma20n01.2864767.0       nwp_sp      9/10 12:58 ST 100 serial       cma19n07   ",
        "cma20n02.2860805.0       nwp_vfy    10/1  04:00 R  100 operation    cma20n03   ",
        "cma20n04.2865560.0       nwp_sp     11/16 07:58 I  100 serial                  ",
        "cma19n02.2865233.0       bcccsmqu    9/6  06:48 I  50  normal                  ",
        "cma20n02.2864013.0       nwp_sp      9/6  07:50 C  100 serial                  ",
    };
    QStringList id_list{
        "cma20n02.2860805.0",
        "cma20n01.2864767.0",
        "cma20n02.2860805.0",
        "cma20n04.2865560.0",
        "cma19n02.2865233.0",
        "cma20n02.2864013.0",
    };

    QStringList owner_list{
        "nwp_vfy",
        "nwp_sp",
        "nwp_vfy",
        "nwp_sp",
        "bcccsmqu",
        "nwp_sp",
    };

    QStringList submitted_list{
        "09/06 04:00",
        "09/10 12:58",
        "10/01 04:00",
        "11/16 07:58",
        "09/06 06:48",
        "09/06 07:50"
    };

    QStringList status_list{
        "R",
        "ST",
        "R",
        "I",
        "I",
        "C",
    };

    QStringList pri_list{
        "100",
        "100",
        "100",
        "100",
        "50",
        "100",
    };

    QStringList class_list{
        "serial",
        "serial",
        "operation",
        "serial",
        "normal",
        "serial",
    };

    QStringList running_on_list{
        "cma20n07",
        "cma19n07",
        "cma20n03",
        "",
        "",
        "",
    };

    for(int i=0; i<lines.length(); i++)
    {
        QTest::newRow(("llq.default." + QString::number(row_no++)).toStdString().c_str())
                << lines[i]
                << id_list[i]
                << owner_list[i]
                << submitted_list[i]
                << status_list[i]
                << pri_list[i]
                << class_list[i]
                << running_on_list[i];
    }
}

void QueryItemTest::testBuildLlqDefaultQueryRow()
{
    QFETCH(QString, line);
    QFETCH(QString, id);
    QFETCH(QString, owner);
    QFETCH(QString, submitted);
    QFETCH(QString, status);
    QFETCH(QString, pri);
    QFETCH(QString, ll_class);
    QFETCH(QString, running_on);

    QList<QStandardItem *> row = QueryItem::buildDefaultQueryRow(line, llq_default_category_list_);

    QCOMPARE(row[0]->text(), id);
    QCOMPARE(row[1]->text(), owner);
    QCOMPARE(row[2]->text(), submitted);
    QCOMPARE(row[3]->text(), status);
    QCOMPARE(row[4]->text(), pri);
    QCOMPARE(row[5]->text(), ll_class);
    QCOMPARE(row[6]->text(), running_on);

}

void QueryItemTest::testBuildLlclassDefaultQueryRow_data()
{

}

void QueryItemTest::testBuildLlclassDefaultQueryRow()
{

}

QTEST_APPLESS_MAIN(QueryItemTest)

#include "tst_query_item_test.moc"
