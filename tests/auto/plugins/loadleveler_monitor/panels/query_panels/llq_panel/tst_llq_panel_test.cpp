#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QPushButton>

#include <loadleveler_monitor/panels/llq_panel.h>
#include <core_plugin/session_system/session.h>

using namespace LoadLevelerMonitor::Panels;
using namespace Core::SessionSystem;

class LlqPanelTest : public QObject
{
    Q_OBJECT

public:
    LlqPanelTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testOperationAction();
    void testSession();
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

void LlqPanelTest::testSession()
{
    QString name, host, port, user, password;
    name = "wangdp@uranus";
    host = "uranus.hpc.nmic.cn";
    port = "22";
    user = "wangdp";
    password = "perilla";

    Session session{name, host, port, user, password};

    LlqPanel panel;
    panel.setSession(session);

    QVERIFY(panel.hasSession());

    Session panel_session = panel.getSession();

    QCOMPARE(panel_session.name_, session.name_);
    QCOMPARE(panel_session.host_, session.host_);
    QCOMPARE(panel_session.port_, session.port_);
    QCOMPARE(panel_session.user_, session.user_);
    QCOMPARE(panel_session.password_, session.password_);

    QMap<QString, QString> session_argument = panel.getSessionArguments();

    QCOMPARE(session_argument["host"], session.host_);
    QCOMPARE(session_argument["port"], session.port_);
    QCOMPARE(session_argument["user"], session.user_);
    QCOMPARE(session_argument["password"], session.password_);

}

QTEST_MAIN(LlqPanelTest)

#include "tst_llq_panel_test.moc"
