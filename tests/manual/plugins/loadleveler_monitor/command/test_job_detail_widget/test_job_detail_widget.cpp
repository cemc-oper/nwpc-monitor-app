#include "test_job_detail_widget.h"
#include "ui_test_job_detail_widget.h"

#include <QTest>
#include <QFile>
#include <vector>
#include <tuple>

using namespace std;
using namespace LoadlevelerMonitor::Widgets;

using JobDetailTestParam = tuple<QString, JobDetailWidget*>;

TestJobDetailWidget::TestJobDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new ::Ui::TestJobDetailWidget)
{
    ui->setupUi(this);

    vector<JobDetailTestParam> params = {
        make_tuple(QString("data/serial_running_job_detail.txt"), ui->serial_running_job_detail_widget),
        make_tuple(QString("data/serial_idle_job_detail.txt"), ui->serial_idle_job_detail_widget),
        make_tuple(QString("data/parallel_running_job_detail.txt"), ui->parallel_running_job_detail_widget),
        make_tuple(QString("data/parallel_idle_job_detail.txt"), ui->parallel_idle_job_detail_widget),
    };

    foreach(JobDetailTestParam param, params)
    {
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
