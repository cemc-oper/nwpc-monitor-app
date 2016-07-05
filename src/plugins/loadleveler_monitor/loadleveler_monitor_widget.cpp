#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

using namespace LoadlevelerMonitor;

LoadlevelerMonitorWidget::LoadlevelerMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadlevelerMonitorWidget)
{
    ui->setupUi(this);
}

LoadlevelerMonitorWidget::~LoadlevelerMonitorWidget()
{
    delete ui;
}
