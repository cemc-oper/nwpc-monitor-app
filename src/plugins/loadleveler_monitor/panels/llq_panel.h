#pragma once

#include <progress_util/shell_command.h>

#include <QWidget>
#include <QPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
class QStandardItemModel;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace Model{
class QueryModel;
}

namespace Chart{
class ModelProcessor;
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
    void slotRequestQuery();

    void slotTemplateActionTriggered(QAction *action);
    void slotStyleActionTriggered(QAction *action);

    // table style
    void slotQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index);

private:
    void setupTemplate();
    void setupStyle();

    void setTableStyleVisibility(bool is_visible);
    void setChartStyleVisibility(bool is_visible);
    void setTextStyleVisibility(bool is_visible);

    // request component
    void setRequestCommandLabel(const QJsonObject &request_object);
    void setRequestTimeLabel(const QDateTime &request_time, const QDateTime &finish_time);

    // table style
    void setQueryModel(QPointer<LoadLevelerMonitor::Model::QueryModel> query_model);

    // chart style
    void updateChartStylePage();
    void showChart(QAction *chart_type_action);

    // text style
    void updateTextStylePage(const QString &str);

    Ui::LlqPanel *ui;
    QPointer<QActionGroup> style_action_group_;
    QVector<QAction *> style_action_list_;

    QPointer<QActionGroup> template_action_group_;
    QVector<QAction *> template_action_list_;

    QPointer<LoadLevelerMonitor::LoadLevelerMonitorWidget> monitor_widget_;
    QPointer<LoadLevelerMonitor::Model::QueryModel> query_model_;

    // chart
    QMap<QAction *, LoadLevelerMonitor::Chart::ModelProcessor*> chart_type_action_map_;
    QPointer<QActionGroup> chart_type_action_group_;
};

}

}
