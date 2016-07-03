#pragma once

#include "iperspective.h"

#include <QMainWindow>
#include <QList>

namespace Core{

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadPerspectives();

    void activatePerspective(int id);

private:
    void addPerspective(IPerspective* perspective);

    Ui::MainWindow *ui;

    QList<IPerspective*> perspective_list_;
};

}
