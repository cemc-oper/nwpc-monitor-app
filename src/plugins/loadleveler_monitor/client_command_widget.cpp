#include "client_command_widget.h"
#include "ui_client_command_widget.h"

#include <python_env_plugin/python_command.h>
#include "loadleveler_monitor_plugin.h"
#include "loadleveler_client.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace PythonEnv;

ClientCommandWidget::ClientCommandWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientCommandWidget),
    python_command_{nullptr}
{
    ui->setupUi(this);
    ui->message_tab_widget->setCurrentIndex(0);

    //setAttribute(Qt::WA_DeleteOnClose, true);
}

ClientCommandWidget::~ClientCommandWidget()
{
    qDebug()<<"[ClientCommandWidget::~ClientCommandWidget] delete";
    delete ui;
}

void ClientCommandWidget::runPythonCommand(QMap<QString, QString> args)
{
    qDebug()<<"[ClientCommandWidget::runPythonCommand] start";
    QStringList arguments;
    PythonCommand* command =  LoadLevelerMonitorPlugin::client()->createPythonCommand();
    connect(command, &PythonCommand::signalStdOutString,
            this, &ClientCommandWidget::receiveResponse);

    connect(command, &PythonCommand::signalStdErrString,
            this, &ClientCommandWidget::setErrorOutputText);

//    connect(command, &PythonCommand::signalFinished,
//            [=](int exit_code, QProcess::ExitStatus status)
//            {
//                qDebug()<<"[ClientCommandWidget::runPythonCommand] exit code:"<<exit_code;
//                qDebug()<<"[ClientCommandWidget::runPythonCommand] exit status:"<<status;
//            }
//    );

    arguments<<"run";
    arguments<<"--host=" + args["host"];
    arguments<<"--port=" + args["port"];
    arguments<<"--user=" + args["user"];
    arguments<<"--password=" + args["password"];
    arguments<<"--command=" + args["command"];

    qDebug()<<arguments;

    LoadLevelerMonitorPlugin::client()->executePythonScript(
        command,
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
        arguments
    );

    setCommandText("loadleveler.py " + arguments.join(" "));

    qDebug()<<"[ClientCommandWidget::runPythonCommand] end";

}

void ClientCommandWidget::setCommandText(const QString &command)
{
    ui->command_edit->setText(command);
}

void ClientCommandWidget::receiveResponse(const QString &response)
{
    setResponseText(response);

    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[ClientCommandWidget::receiveResponse] result is not a json string.";
        return;
    }

    QJsonObject result_object = doc.object();

    QString error_message = result_object["data"].toObject()["result"].toObject()["message"].toObject()["error_output"].toString();
    setErrorOutputText(error_message);

    QString output_message = result_object["data"].toObject()["result"].toObject()["message"].toObject()["output"].toString();
    setOutputText(output_message);
}

void ClientCommandWidget::setOutputText(const QString &output)
{
    ui->output_edit->setText(output);
}

void ClientCommandWidget::setErrorOutputText(const QString &error_output)
{
    ui->error_output_edit->setText(error_output);
}

void ClientCommandWidget::setResponseText(const QString &output)
{
    ui->response_edit->setText(output);
}

void ClientCommandWidget::closeEvent(QCloseEvent *event)
{
    qDebug()<<"[ClientCommandWidget::closeEvent] closeEvent";
    this->deleteLater();
}
