#include <QString>
#include <QtTest>

#include <util/model_view_util.h>

#include <QStandardItem>
#include <QStandardItemModel>
#include <QPointer>
#include <QList>

class ModelViewUtilTest : public QObject
{
    Q_OBJECT

public:
    ModelViewUtilTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testAllItemUnchecked_data();
    void testAllItemUnchecked();

    void testAllItemChecked_data();
    void testAllItemChecked();

    void testGetCheckedRows_data();
    void testGetCheckedRows();

private:
    QPointer<QStandardItemModel> normal_model_;
    QPointer<QStandardItemModel> empty_model_;
};

ModelViewUtilTest::ModelViewUtilTest()
{
}

void ModelViewUtilTest::initTestCase()
{
    normal_model_ = new QStandardItemModel;
    normal_model_->invisibleRootItem()->appendRow(QList<QStandardItem *>()<<new QStandardItem("cell (0,0)")<<new QStandardItem("cell (0,1)"));
    normal_model_->invisibleRootItem()->appendRow(QList<QStandardItem *>()<<new QStandardItem("cell (1,0)")<<new QStandardItem("cell (1,1)"));

    empty_model_ = new QStandardItemModel;
}

void ModelViewUtilTest::cleanupTestCase()
{
    normal_model_->deleteLater();
    empty_model_->deleteLater();
}

void ModelViewUtilTest::testAllItemUnchecked_data()
{
    QTest::addColumn< QPointer<QStandardItemModel> >("model");
    QTest::newRow("normal model") << normal_model_;
    QTest::newRow("empty model") << empty_model_;
}

void ModelViewUtilTest::testAllItemUnchecked()
{
    QFETCH(QPointer<QStandardItemModel>, model);
    Util::ModelView::changeAllItemsCheckState(model, Qt::Unchecked);
    int row_count = normal_model_->invisibleRootItem()->rowCount();
    for(int i=0; i<row_count; i++)
    {
        QCOMPARE(normal_model_->invisibleRootItem()->child(i,0)->checkState(), Qt::Unchecked);
    }
}

void ModelViewUtilTest::testAllItemChecked_data()
{
    QTest::addColumn< QPointer<QStandardItemModel> >("model");
    QTest::newRow("normal model") << normal_model_;
    QTest::newRow("empty model") << empty_model_;
}

void ModelViewUtilTest::testAllItemChecked()
{
    QFETCH(QPointer<QStandardItemModel>, model);
    Util::ModelView::changeAllItemsCheckState(model, Qt::Checked);
    int row_count = normal_model_->invisibleRootItem()->rowCount();
    for(int i=0; i<row_count; i++)
    {
        QCOMPARE(normal_model_->invisibleRootItem()->child(i,0)->checkState(), Qt::Checked);
    }
}

void ModelViewUtilTest::testGetCheckedRows_data()
{
    QPointer<QStandardItemModel> model_ex1 = new QStandardItemModel;
    model_ex1->invisibleRootItem()->appendRow(QList<QStandardItem *>()<<new QStandardItem("cell (0,0)")<<new QStandardItem("cell (0,1)"));
    model_ex1->invisibleRootItem()->appendRow(QList<QStandardItem *>()<<new QStandardItem("cell (1,0)")<<new QStandardItem("cell (1,1)"));
    model_ex1->invisibleRootItem()->appendRow(QList<QStandardItem *>()<<new QStandardItem("cell (2,0)")<<new QStandardItem("cell (2,1)"));
    model_ex1->invisibleRootItem()->appendRow(QList<QStandardItem *>()<<new QStandardItem("cell (3,0)")<<new QStandardItem("cell (3,1)"));
    model_ex1->invisibleRootItem()->child(1)->setCheckState(Qt::Checked);
    model_ex1->invisibleRootItem()->child(2)->setCheckState(Qt::Checked);

    QTest::addColumn< QPointer<QStandardItemModel> >("model");
    QTest::addColumn<QList<int>>("selected_rows");

    QPointer<QStandardItemModel> empty_model = new QStandardItemModel;

    QTest::newRow("normal_model")
            << model_ex1
            << QList<int>()<<1<<2;
    QTest::newRow("empty model")
            << empty_model
            << QList<int>();
}

void ModelViewUtilTest::testGetCheckedRows()
{
    QFETCH(QPointer<QStandardItemModel>, model);
    QFETCH(QList<int>, selected_rows);

    QList<int> get_selected_rows = Util::ModelView::getCheckedRows(model);

    QCOMPARE(get_selected_rows.size(), selected_rows.size());
    for(int i=0; i<get_selected_rows.size(); i++)
    {
        QCOMPARE(get_selected_rows[i], selected_rows[i]);
    }
}

QTEST_APPLESS_MAIN(ModelViewUtilTest)

#include "tst_model_view_util_test.moc"
