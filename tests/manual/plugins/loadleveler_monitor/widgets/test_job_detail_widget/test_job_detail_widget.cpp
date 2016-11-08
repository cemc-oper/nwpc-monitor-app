#include "test_job_detail_widget.h"
#include "ui_test_job_detail_widget.h"

#include <plugin_manager/plugin_manager.h>
#include <loadleveler_monitor/loadleveler_monitor_plugin.h>
#include <core_plugin/core_plugin.h>

#include <QTest>
#include <QFile>
#include <vector>
#include <tuple>

using namespace std;
using namespace PluginSystem;
using namespace Core;
using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Widgets;

using JobDetailTestParam = tuple<QString, JobDetailWidget*>;

TestJobDetailWidget::TestJobDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new ::Ui::TestJobDetailWidget)
{
    QStringList args;
    QString error_string;
    PluginManager *manager = new PluginManager;
    CorePlugin *core_plugin = new CorePlugin;
    core_plugin->initialize(args, &error_string);
    LoadLevelerMonitorPlugin *loadleveler_monitor_plugin = new LoadLevelerMonitorPlugin;
    loadleveler_monitor_plugin->initialize(args, &error_string);

    ui->setupUi(this);
    session_.host_ = "uranus.hpc.nmic.cn";
    session_.port_ = "22";
    session_.user_ = "wangdp";
    session_.password_ = "perilla";

    vector<JobDetailTestParam> params = {
        make_tuple(QString("data/serial_running_job_detail.txt"), ui->serial_running_job_detail_widget),
        make_tuple(QString("data/serial_idle_job_detail.txt"), ui->serial_idle_job_detail_widget),
        make_tuple(QString("data/parallel_running_job_detail.txt"), ui->parallel_running_job_detail_widget),
        make_tuple(QString("data/parallel_idle_job_detail.txt"), ui->parallel_idle_job_detail_widget),
    };

    foreach(JobDetailTestParam param, params)
    {
        get<1>(param)->setSession(session_);
        QString response_file_path = QFINDTESTDATA(get<0>(param));

        QFile response_file{response_file_path};
        response_file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString response{response_file.readAll()};
        response_file.close();
        get<1>(param)->receiveResponse(response);
    }
}

TestJobDetailWidget::~TestJobDetailWidget()
{
    delete ui;
}
