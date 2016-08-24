#include "widget.h"
#include "ui_widget.h"

#include <python_env_plugin/python_engine.h>
#include <python_env_plugin/python_command.h>

#include <loadleveler_monitor/model/query_model.h>

#include <QtDebug>

using namespace PythonEnv;
using namespace LoadLevelerMonitor::Model;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    python_engine_(new PythonEngine),
    ll_manager_{new LlqCommandManager{this}}
{
    ui->setupUi(this);

    python_engine_->setPythonDistributionDir(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35"
    );
    python_engine_->setPythonExecutableProgramPath(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35\\python.exe"
    );

    LlqCommandManager::initialize();
}

Widget::~Widget()
{
    delete ui;
    delete python_engine_;
}

void Widget::on_btn_run_success_python_script_clicked()
{
    QStringList arg_list;
    PythonCommand* command = python_engine_->createPythonCommand();
    connect(command, &PythonCommand::signalFinished,
            this, &Widget::slotCommandFinished);

    arg_list<<"run";
    arg_list<<"--host=uranus.hpc.nmic.cn";
    arg_list<<"--port=22";
    arg_list<<"--user=wangdp";
    arg_list<<"--password=perilla";
    arg_list<<"--command=" + ui->loadleveler_command->text();

    python_engine_->executePythonScript(
                command,
                "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app\\src\\plugins\\loadleveler_monitor\\nwpc_loadleveler\\loadleveler.py",
                arg_list
    );

}

void Widget::on_btn_run_nonexist_python_script_clicked()
{
    QStringList arg_list;
    PythonCommand* command = python_engine_->createPythonCommand();
    connect(command, &PythonCommand::signalSuccess,
            [=]()
            {
                qDebug()<<"[on_btn_run_nonexist_python_script_clicked] succcess";
            }
    );
    python_engine_->executePythonScript(
                command,
                "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app"
                "\\tests\\manual\\plugins\\python_env_plugin\\pyton_run_script\\helloworld.py1",
                arg_list
    );
}

void Widget::on_btn_run_nonexist_python_exe_clicked()
{

}

void Widget::slotCommandFinished(const ProgressUtil::ShellCommandResponse &response)
{
    qDebug()<<response.std_out_;
    QueryModel *model = LlqCommandManager::buildQueryModelFromResponse(response.std_out_);
    ui->view->setModel(model);
}
