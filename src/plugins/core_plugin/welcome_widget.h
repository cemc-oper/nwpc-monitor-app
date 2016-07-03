#pragma once

#include <QWidget>

namespace Core{

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = 0);
    ~WelcomeWidget();

private:
    Ui::WelcomeWidget *ui;
};

}
