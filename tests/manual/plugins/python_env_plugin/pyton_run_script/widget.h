#ifndef WIDGET_H
#define WIDGET_H

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
    void on_btn_run_python_script_clicked();

private:
    Ui::Widget *ui;

    PythonEnv::PythonEngine* python_engine_;
};

#endif // WIDGET_H
