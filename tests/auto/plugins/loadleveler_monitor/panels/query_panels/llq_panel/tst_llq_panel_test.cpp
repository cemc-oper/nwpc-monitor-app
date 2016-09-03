#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QPushButton>

#include <loadleveler_monitor/panels/llq_panel.h>

using namespace LoadLevelerMonitor::Panels;

class LlqPanelTest : public QObject
{
    Q_OBJECT

public:
    LlqPanelTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testOperationAction();
};

LlqPanelTest::LlqPanelTest()
{
}

void LlqPanelTest::initTestCase()
{
}

void LlqPanelTest::cleanupTestCase()
{
}

void LlqPanelTest::testOperationAction()
{
    LlqPanel panel;

    QPushButton *cancel_button = panel.findChild<QPushButton *>("LlqPanel.OperationAction.cancel.button");
    QVERIFY(cancel_button);
    QPushButton *release_button = panel.findChild<QPushButton *>("LlqPanel.OperationAction.release.button");
    QVERIFY(release_button);

}

QTEST_MAIN(LlqPanelTest)

#include "tst_llq_panel_test.moc"
