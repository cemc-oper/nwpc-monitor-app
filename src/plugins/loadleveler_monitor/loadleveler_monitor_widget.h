#pragma once

#include <QWidget>

namespace LoadLevelerMonitor{

namespace Ui {
class LoadLevelerMonitorWidget;
}

class LoadLevelerMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadLevelerMonitorWidget(QWidget *parent = 0);
    ~LoadLevelerMonitorWidget();

private:
    Ui::LoadLevelerMonitorWidget *ui;
};

}
