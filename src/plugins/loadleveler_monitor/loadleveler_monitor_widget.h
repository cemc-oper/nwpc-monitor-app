#pragma once

#include <QWidget>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QButtonGroup;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{
class JobQueryModel;
}

namespace Ui {
class LoadLevelerMonitorWidget;
}

class LoadLevelerMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadLevelerMonitorWidget(QWidget *parent = 0);
    ~LoadLevelerMonitorWidget();

    void setJobQueryModel(QPointer<LoadLevelerModel::JobQueryModel> job_query_model);

private slots:
    void slotLlqQueryRecordContextMenuRequest(const QPoint& pos);

    void slotRequestQuery();

private:
    void changeAllItemsCheckState(Qt::CheckState check_state);

    Ui::LoadLevelerMonitorWidget *ui;

    QPointer<LoadLevelerModel::JobQueryModel> job_query_model_;

    QPointer<QButtonGroup> panel_button_group_;
};

}
