#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QAction>
#include <QPointer>
#include <QVector>
#include <QPushButton>

#include <loadleveler_monitor/panels/table_style_page.h>
#include <loadleveler_monitor/model/query_model.h>

using namespace LoadLevelerMonitor::Panels;
using namespace LoadLevelerMonitor::Model;

class TableStylePageTest : public QObject
{
    Q_OBJECT

public:
    TableStylePageTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testModel_data();
    void testModel();

    void testOperationButtons();

private:

};

TableStylePageTest::TableStylePageTest()
{
}

void TableStylePageTest::initTestCase()
{
}

void TableStylePageTest::cleanupTestCase()
{
}

void TableStylePageTest::testModel_data()
{
    QTest::addColumn<QPointer<QueryModel>>("query_mdoel");

    QTest::newRow("empty model")
            <<QPointer<QueryModel>(new QueryModel);
}

void TableStylePageTest::testModel()
{
    QFETCH(QPointer<QueryModel>, query_mdoel);

    TableStylePage page;
    page.setModel(query_mdoel);

    page.clear();
}


void TableStylePageTest::testOperationButtons()
{
    int x = 0;
    QPointer<QAction> add_action = new QAction{"add action"};
    add_action->setObjectName("add_action");
    connect(add_action, &QAction::triggered, [&x](bool){
        x += 1;
    });

    int y = 1;
    QPointer<QAction> multi_action = new QAction{"multi action"};
    multi_action->setObjectName("multi_action");
    connect(multi_action, &QAction::triggered, [&y](bool){
        y *= 2;
    });

    QVector<QPointer<QAction>> action_vector;
    action_vector.push_back(add_action);
    action_vector.push_back(multi_action);

    TableStylePage page;
    page.setOperationButtons(action_vector);

    QPushButton *add_button = page.findChild<QPushButton*>(add_action->objectName() + ".button");
    QVERIFY(add_button);
    QPushButton *multi_button = page.findChild<QPushButton*>(multi_action->objectName() + ".button");
    QVERIFY(multi_button);

    QTest::mouseClick(add_button, Qt::LeftButton);
    QCOMPARE(x, 1);

    QTest::mouseClick(multi_button, Qt::LeftButton);
    QCOMPARE(y, 2);

    page.setOperationButtons(QVector<QPointer<QAction>>());

    add_action->deleteLater();
    multi_action->deleteLater();
}

QTEST_MAIN(TableStylePageTest)

#include "tst_table_style_page_test.moc"
