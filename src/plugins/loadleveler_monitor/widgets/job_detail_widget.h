#pragma once

#include "../loadleveler_monitor_global.h"

#include <core_plugin/session_system/session.h>

#include <QWidget>
#include <QPointer>
#include <QVector>
#include <QHash>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
class QStandardItemModel;
QT_END_NAMESPACE


namespace LoadLevelerMonitor{

class LoadLevelerClient;

namespace Widgets{

namespace Ui {
class JobDetailWidget;
}

class LOADLEVELER_MONITOR_EXPORT JobDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JobDetailWidget(QWidget *parent = 0);
    ~JobDetailWidget();

    void setSession(const Core::SessionSystem::Session &session);
    void setJobId(const QString &job_id);

public slots:
    void receiveResponse(const QString &response);

private slots:
    void slotStyleActionTriggered(QAction *action);
    void slotPropertyModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index);


    // TODO: repeat is evil: text browser
    void slotScrollToEnd(bool flag);
    void scrollToEnd();

private:
    void setupStyle();

    void setResponseStylePage(const QString &response);
    void setOutputStylePage(const QString &output);
    void setTreeStylePage(const QString &output);

    void requestSeeFile(const QString &file_path);

    static QString getTextByLabel(const QString &label, const QStringList &record);

    Ui::JobDetailWidget *ui;

    QVector<QAction *> style_action_list_;
    QPointer<QActionGroup> style_action_group_;

    QPointer<QStandardItemModel> property_model_;
    QHash<QString, QVariant> property_map_;

    // session
    Core::SessionSystem::Session session_;

    QPointer<LoadLevelerClient> client_;
    bool is_scroll_to_end_;
};

}

}
