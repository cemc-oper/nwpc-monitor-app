#pragma once

#include <QDockWidget>

namespace Core{

namespace Views{

namespace Ui {
class OutputDockWidget;
}

class OutputDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit OutputDockWidget(QWidget *parent = 0);
    ~OutputDockWidget();

private:
    Ui::OutputDockWidget *ui;
};

}

}