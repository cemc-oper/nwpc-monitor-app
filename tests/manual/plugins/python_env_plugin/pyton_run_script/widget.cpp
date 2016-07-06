#include "widget.h"
#include "ui_widget.h"

#include <python_env_plugin/python_engine.h>

using namespace PythonEnv;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    python_engine_(new PythonEngine)
{
    ui->setupUi(this);

    python_engine_->setPythonDistributionDir(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35"
    );
    python_engine_->setPythonExecutableProgramPath(
        "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app-playground\\python\\python35\\python.exe"
    );
}

Widget::~Widget()
{
    delete ui;
    delete python_engine_;
}

void Widget::on_btn_run_python_script_clicked()
{
    QStringList arg_list;
    python_engine_->executePythonScript(
                "D:\\windroc\\project\\2016\\nwpc-monitor-app\\nwpc-monitor-app"
                "\\tests\\manual\\plugins\\python_env_plugin\\pyton_run_script\\helloworld.py",
                arg_list
    );
}
