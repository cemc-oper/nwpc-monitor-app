#pragma once

#include <QWidget>
#include <core_plugin/session_system/session.h>

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
    Core::SessionSystem::Session session_;
};
