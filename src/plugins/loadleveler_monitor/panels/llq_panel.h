#pragma once

#include <QWidget>
#include <QPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{
class JobQueryModel;
}

class LoadLevelerMonitorWidget;

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

    void setMonitorWidget(LoadLevelerMonitor::LoadLevelerMonitorWidget *widget);

    void setJobQueryModel(QPointer<LoadLevelerMonitor::LoadLevelerModel::JobQueryModel> job_query_model);

private slots:
    void slotStyleActionTriggered(QAction *action);
    void slotTemplateActionTriggered(QAction *action);

    void slotRequestQuery();

    void slotQueryRecordContextMenuRequest(const QPoint& pos);  

private:
    void setupTemplate();
    void setupStyle();

    void changeAllItemsCheckState(Qt::CheckState check_state);

    Ui::LlqPanel *ui;
    QPointer<QActionGroup> style_action_group_;
    QVector<QAction *> style_action_list_;

    QPointer<QActionGroup> template_action_group_;
    QVector<QAction *> template_action_list_;

    QPointer<LoadLevelerMonitor::LoadLevelerMonitorWidget> monitor_widget_;

    QPointer<LoadLevelerMonitor::LoadLevelerModel::JobQueryModel> job_query_model_;
};

}

}
