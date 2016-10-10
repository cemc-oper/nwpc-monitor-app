#ifndef WIDGET_H
#define WIDGET_H


#include <loadleveler_monitor/model/llq_command_manager.h>

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    LoadLevelerMonitor::Model::LlqCommandManager *ll_manager_;
};

#endif // WIDGET_H
