#include "test_job_detail_widget.h"
#include "ui_test_job_detail_widget.h"

#include <QTest>
#include <QFile>

TestJobDetailWidget::TestJobDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestJobDetailWidget)
{
    ui->setupUi(this);

    QString response_file_path = QFINDTESTDATA("data/parallel_job_detail.txt");

    QFile response_file{response_file_path};
    response_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString response{response_file.readAll()};
    response_file.close();
    ui->job_detail_widget->receiveResponse(response);
}

TestJobDetailWidget::~TestJobDetailWidget()
{
    delete ui;
}
