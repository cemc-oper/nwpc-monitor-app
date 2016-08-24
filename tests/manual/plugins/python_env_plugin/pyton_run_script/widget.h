#ifndef WIDGET_H
#define WIDGET_H

#include <loadleveler_monitor/model/llq_command_manager.h>
#include <python_env_plugin/python_command.h>
#include <QWidget>

namespace PythonEnv{
class PythonEngine;
}

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btn_run_success_python_script_clicked();

    void on_btn_run_nonexist_python_script_clicked();

    void on_btn_run_nonexist_python_exe_clicked();

    void slotCommandFinished(const ProgressUtil::ShellCommandResponse &response);

private:
    Ui::Widget *ui;

    PythonEnv::PythonEngine* python_engine_;

    LoadLevelerMonitor::Model::LlqCommandManager *ll_manager_;
};

#endif // WIDGET_H
