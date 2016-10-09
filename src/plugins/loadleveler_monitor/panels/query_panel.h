#pragma once

#include "../loadleveler_monitor_global.h"
#include <progress_util/shell_command.h>
#include <core_plugin/session_system/session.h>

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

class LOADLEVELER_MONITOR_EXPORT QueryPanel : public QWidget
{
    Q_OBJECT

public:
    explicit QueryPanel(QWidget *parent = 0);
    ~QueryPanel();

    void setSession(const Core::SessionSystem::Session& session);
    Core::SessionSystem::Session getSession() const;
    bool hasSession() const;
    QMap<QString, QString> getSessionArguments();

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
    void setRequestTimeLable(const QDateTime &request_time);
    void setResponseSecondLabel(const QDateTime &request_time, const QDateTime &finish_time);
    void setResponseHandleSecondLabel(const QDateTime &received_time, const QDateTime &finish_time);

    // table style
    void setQueryModel(QPointer<LoadLevelerMonitor::Model::QueryModel> query_model);

    // chart style
    virtual void updateChartStylePage() = 0;
    void showChart(QAction *chart_type_action);

    // text style
    void updateTextStylePage(const QString &str);

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

    // session
    Core::SessionSystem::Session session_;
};

}

}
