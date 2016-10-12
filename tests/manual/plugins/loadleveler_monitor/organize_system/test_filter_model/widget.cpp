#include "widget.h"
#include "ui_widget.h"

#include <loadleveler_monitor/model/query_model.h>
#include <loadleveler_monitor/model/llq_command_manager.h>

#include <QFile>
#include <QTest>
#include <QtDebug>

using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    ll_manager_{new LlqCommandManager{this}}
{
    ui->setupUi(this);

    init();

    ui->source_table_view->setModel(model_);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    LlqCommandManager::initialize();

    QString response_file_path = QFINDTESTDATA("../data/response.json");
    QString llq_output_file_path = QFINDTESTDATA("../data/llq_output.txt");

    QFile llq_output_file{llq_output_file_path};
    llq_output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString llq_output{llq_output_file.readAll()};
    llq_output_file.close();

    QFile response_file{response_file_path};
    response_file.open( QIODevice::ReadOnly | QIODevice::Text);
    QByteArray b = response_file.readAll();
    b.replace(QString("\"output\": \"\"").toStdString().c_str(),
              QString("\"output\": \"" + llq_output + "\"").toStdString().c_str());

    model_ = LlqCommandManager::buildQueryModelFromResponse(b);
}
