#pragma once

#include <QWidget>
#include <QPointer>

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
    void on_query_button_clicked();

private:
    void changeAllItemsCheckState(Qt::CheckState check_state);

    Ui::LoadLevelerMonitorWidget *ui;

    QPointer<LoadLevelerModel::JobQueryModel> job_query_model_;
};

}
