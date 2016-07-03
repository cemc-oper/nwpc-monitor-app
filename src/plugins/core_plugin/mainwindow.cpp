#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iperspective.h"

#include <plugin_manager/plugin_manager.h>
#include <QtDebug>

using namespace Core;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPerspectives()
{
    QList<IPerspective*> perspectives = PluginManager::getObjects<IPerspective>();

    foreach(IPerspective* pers, perspectives)
    {
        qDebug()<<pers->displayName();
        addPerspective(pers);
    }
}

void MainWindow::activatePerspective(int id)
{
    IPerspective* pers = perspective_list_[id];
    QWidget* widget = pers->widget();
    ui->main_grid_layout->addWidget(widget, 0, 0);
}

void MainWindow::addPerspective(IPerspective *perspective)
{
    perspective_list_.append(perspective);
}
