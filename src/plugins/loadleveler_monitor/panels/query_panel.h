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
class QueryPanel;
}

class QueryPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QueryPanel(QWidget *parent = 0);
    ~QueryPanel();

    void setMonitorWidget(LoadLevelerMonitor::LoadLevelerMonitorWidget *widget);

public slots:
    virtual void slotRequestQuery() = 0;
    virtual void slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response) = 0;

protected slots:
    void slotTemplateActionTriggered(QAction *action);
    void slotStyleActionTriggered(QAction *action);

    // table style
    virtual void slotQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index) = 0;

protected:
    virtual void setupTemplate() = 0;
    virtual void setupStyle() = 0;

    void setTableStyleVisibility(bool is_visible);
    void setChartStyleVisibility(bool is_visible);
    void setTextStyleVisibility(bool is_visible);

    // request component
    void setRequestCommandLabel(const QJsonObject &request_object);
    void setRequestTimeLabel(const QDateTime &request_time, const QDateTime &finish_time);

    // table style
    void setQueryModel(QPointer<LoadLevelerMonitor::Model::QueryModel> query_model);

    // chart style
    virtual void updateChartStylePage() = 0;
    void showChart(QAction *chart_type_action);

    // text style
    void updateTextStylePage(const QString &str);

    QPointer<LoadLevelerMonitor::LoadLevelerMonitorWidget> monitor_widget_;

    Ui::QueryPanel *ui;
    QPointer<QActionGroup> style_action_group_;
    QVector<QAction *> style_action_list_;
    QPointer<QActionGroup> template_action_group_;
    QVector<QAction *> template_action_list_;

    // model
    QPointer<LoadLevelerMonitor::Model::QueryModel> query_model_;

    // chart
    QMap<QAction *, LoadLevelerMonitor::Chart::ModelProcessor*> chart_type_action_map_;
    QPointer<QActionGroup> chart_type_action_group_;
};

}

}
