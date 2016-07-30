#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

#include "loadleveler_monitor_plugin.h"
#include "loadleveler_client.h"

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

void LoadLevelerMonitor::LoadLevelerMonitorWidget::on_query_button_clicked()
{
    LoadLevelerMonitorPlugin::client()->runLlqCommand();
}
