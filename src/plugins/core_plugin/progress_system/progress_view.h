#pragma once

#include <QWidget>

namespace Core{

namespace ProgressSystem{

namespace Ui {
class ProgressView;
}

class ProgressView : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressView(QWidget *parent = 0);
    ~ProgressView();

    void addProgressItemWidget(QWidget *widget);

private:
    Ui::ProgressView *ui;
};

}

}
