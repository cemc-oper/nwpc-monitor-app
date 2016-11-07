#pragma once

#include <QWidget>

namespace Ui {
class TestJobDetailWidget;
}

class TestJobDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestJobDetailWidget(QWidget *parent = 0);
    ~TestJobDetailWidget();

private:
    Ui::TestJobDetailWidget *ui;
};
