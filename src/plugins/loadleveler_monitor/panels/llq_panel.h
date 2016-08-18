#pragma once

#include <QWidget>
#include <QPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace Panels{

namespace Ui {
class LlqPanel;
}

class LlqPanel : public QWidget
{
    Q_OBJECT

public:
    explicit LlqPanel(QWidget *parent = 0);
    ~LlqPanel();

private slots:
    void slotStyleActionTriggered(QAction *action);

private:
    void setupStyle();

    Ui::LlqPanel *ui;
    QPointer<QActionGroup> style_action_group_;
    QPointer<QActionGroup> template_action_group_;

    QVector<QAction *> style_action_list_;
};

}

}
