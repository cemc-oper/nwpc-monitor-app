#include "widget.h"
#include "ui_widget.h"

#include <progress_util/shell_command.h>
#include <loadleveler_monitor/model/llq_command_manager.h>

#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
#include <QtDebug>


using namespace LoadLevelerMonitor::Model;
using namespace ProgressUtil;
using namespace LoadLevelerMonitor;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    LlqCommandManager::initialize();

    QString response_file_path = QFINDTESTDATA("data/response.json");
    QString llq_output_file_path = QFINDTESTDATA("data/llq_output.txt");

    QFile llq_output_file{llq_output_file_path};
    llq_output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString llq_output{llq_output_file.readAll()};
    llq_output_file.close();


    QFile response_file{response_file_path};
    response_file.open( QIODevice::ReadOnly | QIODevice::Text);
    QByteArray b = response_file.readAll();
    b.replace(QString("\"output\": \"\"").toStdString().c_str(),
              QString("\"output\": \"" + llq_output + "\"").toStdString().c_str());

    QJsonDocument doc = QJsonDocument::fromJson(b);
    response_file.close();
    QJsonObject object = doc.object();

    qDebug()<<object;


    ShellCommandResponse response;
    response.request_date_time_ = QDateTime::currentDateTime();
    response.exit_code_ = 0;
    response.exit_status_ = QProcess::NormalExit;
    response.std_out_ = b;
    response.std_err_ = "";

    ui->llq_panel->slotReciveCommandResponse(response);
}

Widget::~Widget()
{
    delete ui;
}
