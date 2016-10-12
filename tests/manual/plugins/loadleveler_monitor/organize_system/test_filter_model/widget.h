#pragma once

#include <QWidget>
#include <QPointer>

namespace LoadLevelerMonitor{
namespace Model{
class LlqCommandManager;
class QueryModel;
}
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

private:
    void init();

    Ui::Widget *ui;
    QPointer<LoadLevelerMonitor::Model::LlqCommandManager> ll_manager_;
    QPointer<LoadLevelerMonitor::Model::QueryModel> model_;
};
