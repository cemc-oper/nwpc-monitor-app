#pragma once

#include "../loadleveler_monitor_global.h"
#include <QWidget>
#include <QPointer>
#include <QVector>

QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
QT_END_NAMESPACE


namespace LoadlevelerMonitor{

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
    void setupStyleActions();

    void setResponseStylePage(const QString &response);
    void setOutputStylePage(const QString &output);

    Ui::JobDetailWidget *ui;

    QVector<QAction *> style_action_list_;
    QPointer<QActionGroup> style_action_group_;

};

}

}
