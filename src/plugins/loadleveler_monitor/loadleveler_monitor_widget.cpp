#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

using namespace LoadLevelerMonitor;

LoadLevelerMonitorWidget::LoadLevelerMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadLevelerMonitorWidget)
{
    ui->setupUi(this);
}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
}
