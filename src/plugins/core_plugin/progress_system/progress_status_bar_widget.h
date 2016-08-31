#pragma once

#include <QWidget>

namespace Core{

namespace ProgressSystem{

namespace Ui {
class ProgressStatusBarWidget;
}

class ProgressStatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressStatusBarWidget(QWidget *parent = 0);
    ~ProgressStatusBarWidget();

    void setProgressRange(int min_value, int max_value);

public slots:
    void slotSetProgressValue(int value);

private:
    Ui::ProgressStatusBarWidget *ui;
};

}

}
