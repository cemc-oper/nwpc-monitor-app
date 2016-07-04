#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iperspective.h"

#include <plugin_manager/plugin_manager.h>

#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QSignalMapper>
#include <QtDebug>

using namespace Core;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    perspective_tool_bar_(new QToolBar(this)),
    perspective_action_group_(new QActionGroup(this)),
    perspective_signal_mapper_(new QSignalMapper(this))
{
    ui->setupUi(this);

    addToolBar(perspective_tool_bar_);
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

    // remove actions
    foreach(QAction* action, perspective_action_list_)
    {
        perspective_action_group_->removeAction(action);
        perspective_signal_mapper_->removeMappings(action);
    }

    perspective_id_to_action_map_.clear();

    while(!perspective_action_list_.isEmpty())
    {
        QAction* action = perspective_action_list_.first();
        perspective_action_list_.pop_front();
        delete action;
    }

    // add perspective tool bar
    foreach(IPerspective* pers, perspective_list_)
    {
        QAction* action = new QAction(pers->displayName());
        action->setCheckable(true);
        action->setData(QVariant(pers->id()));
        perspective_action_list_.push_back(action);
        perspective_id_to_action_map_[pers->id()] = action;
        perspective_action_group_->addAction(action);
    }
    foreach(QAction* action, perspective_action_list_)
    {
        perspective_tool_bar_->addAction(action);
    }
    connect(perspective_action_group_, &QActionGroup::triggered, this, &MainWindow::slotPerspectiveActionTriggered);

}

void MainWindow::activatePerspective(QString id)
{
    QAction* active_action;
    if(!perspective_id_to_action_map_.contains(id))
    {
        qWarning()<<"[MainWindow::activatePerspective] can't find perspective "<<id;
        return;
    }

    active_action = perspective_id_to_action_map_[id];
    active_action->setChecked(true);

    //NOTE: action的setChecked不触发QActionGroup的triggered信号，所以强制执行该slot
    slotActivatePerspective(id);
}

void MainWindow::slotPerspectiveActionTriggered(QAction *action)
{
    if(action->isChecked())
    {
        QString id = action->data().toString();
        slotActivatePerspective(id);
    }
}

void MainWindow::slotActivatePerspective(QString id)
{
    int index = perspectiveIndex(id);
    if(index < 0)
    {
        qWarning()<<"[MainWindow::activatePerspective] can't find perspective "<<id;
        return;
    }
    IPerspective* pers = perspective_list_[index];
    QWidget* widget = pers->widget();
    ui->main_grid_layout->addWidget(widget, 0, 0);
}

void MainWindow::addPerspective(IPerspective *perspective)
{
    perspective_list_.append(perspective);
}

int MainWindow::perspectiveIndex(QString id)
{
    for(int i=0; i<perspective_list_.length(); i++)
    {
        if(perspective_list_[i]->id() == id)
        {
            return i;
        }
    }
    return -1;
}
