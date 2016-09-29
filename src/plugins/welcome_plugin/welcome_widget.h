#pragma once

#include <QWidget>

namespace Welcome{

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = 0);
    ~WelcomeWidget();

private slots:

private:
    Ui::WelcomeWidget *ui;
};

}
