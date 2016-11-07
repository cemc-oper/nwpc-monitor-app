#pragma once

#include "../loadleveler_monitor_global.h"
#include <QWidget>
#include <QPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
class QStandardItemModel;
QT_END_NAMESPACE


namespace LoadLevelerMonitor{

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

    void setJobId(const QString &job_id);

public slots:
    void receiveResponse(const QString &response);

private slots:
    void slotStyleActionTriggered(QAction *action);

private:
    void setupStyle();

    void setResponseStylePage(const QString &response);
    void setOutputStylePage(const QString &output);
    void setTreeStylePage(const QString &output);

    static QString getTextByLabel(const QString &label, const QStringList &record);

    Ui::JobDetailWidget *ui;

    QVector<QAction *> style_action_list_;
    QPointer<QActionGroup> style_action_group_;

    QPointer<QStandardItemModel> property_model_;

};

}

}
