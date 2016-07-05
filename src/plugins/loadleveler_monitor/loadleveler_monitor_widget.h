#pragma once

#include <QWidget>

namespace LoadlevelerMonitor{

namespace Ui {
class LoadlevelerMonitorWidget;
}

class LoadlevelerMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadlevelerMonitorWidget(QWidget *parent = 0);
    ~LoadlevelerMonitorWidget();

private:
    Ui::LoadlevelerMonitorWidget *ui;
};

}
