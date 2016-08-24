#pragma once

#include <progress_util/shell_command.h>

#include <QWidget>
#include <QPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace Model{
class QueryModel;
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

public slots:
    void slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response);

private slots:
    void slotStyleActionTriggered(QAction *action);
    void slotTemplateActionTriggered(QAction *action);

    void slotRequestQuery();

    void slotQueryRecordContextMenuRequest(const QPoint& pos);  

private:
    void setupTemplate();
    void setupStyle();

    void setTableStyleVisibility(bool is_visible);
    void setChartStyleVisibility(bool is_visible);
    void setTextStyleVisibility(bool is_visible);

    void setJobQueryModel(QPointer<LoadLevelerMonitor::Model::QueryModel> job_query_model);
    void setCommandTime(const QDateTime &request_time, const QDateTime &finish_time);

    void updateTextStylePage(const QString &str);

    // table style
    void changeAllItemsCheckState(Qt::CheckState check_state);

    Ui::LlqPanel *ui;
    QPointer<QActionGroup> style_action_group_;
    QVector<QAction *> style_action_list_;

    QPointer<QActionGroup> template_action_group_;
    QVector<QAction *> template_action_list_;

    QPointer<LoadLevelerMonitor::LoadLevelerMonitorWidget> monitor_widget_;
    QPointer<LoadLevelerMonitor::Model::QueryModel> job_query_model_;
};

}

}
