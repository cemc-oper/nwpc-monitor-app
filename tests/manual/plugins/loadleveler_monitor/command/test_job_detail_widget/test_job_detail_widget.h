#ifndef TEST_JOB_DETAIL_WIDGET_H
#define TEST_JOB_DETAIL_WIDGET_H

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

#endif // TEST_JOB_DETAIL_WIDGET_H
