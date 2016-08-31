#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "perspective_system/iperspective.h"
#include "core_plugin_constants.h"
#include "action_system/action.h"
#include "action_system/action_manager.h"
#include "action_system/action_container.h"
#include "view_system/dock_view.h"
#include "view_system/view_spec.h"
#include "view_system/view_manager.h"
#include "views/console_dock_widget.h"
#include "perspective_system/perspective_manager.h"
#include "progress_system/progress_manager.h"
#include "progress_system/progress_status_bar_widget.h"

#include <plugin_manager/plugin_manager.h>

#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include <QDockWidget>
#include <QSplitter>
#include <QtDebug>

using namespace Core;
using namespace PluginSystem;
using namespace Core::ViewSystem;
using namespace Core::Views;
using namespace Core::PerspectiveSystem;
using namespace Core::ProgressSystem;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    perspective_tool_bar_(new QToolBar(tr("Perspective"), this))
{
    ui->setupUi(this);

    addToolBar(perspective_tool_bar_);

    registerMainActionContainers();
    registerMainActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{

}

void MainWindow::pluginsInitialized()
{
    loadPerspectives();
    loadViews();
    initStatusBar();
    activatePerspective("welcome");
    show();
}

void MainWindow::aboutToShutdown()
{
    hide();
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
    IPerspective* pers = PerspectiveManager::perspective(id);
    if(pers == nullptr)
    {
        qWarning()<<"[MainWindow::activatePerspective] can't find perspective "<<id;
        return;
    }

    QWidget* widget = pers->widget();
    QLayoutItem *item = ui->main_grid_layout->itemAtPosition(0,0);
    if(item==0)
    {
        ui->main_grid_layout->addWidget(widget, 0, 0);
    }
    else
    {
        item->widget()->hide();
        ui->main_grid_layout->replaceWidget(item->widget(), widget);
        widget->show();
    }

    ConsoleDockWidget::info(ConsoleDockWidget::GeneralPanelId, "perspective active: " + pers->id());
}

void MainWindow::registerMainActionContainers()
{
    QMenu *menu = nullptr;
    ActionContainer *menu_bar_container = ActionManager::createMenuBar(Constrants::MenuBar::MENU_BAR);

    setMenuBar(menu_bar_container->menuBar());

    ActionContainer *file_menu = ActionManager::createMenu(Constrants::Menu::MENU_FILE);
    menu = file_menu->menu();
    menu->setTitle(tr("&File"));
    menu_bar_container->addMenu(file_menu);

    ActionContainer *window_menu = ActionManager::createMenu(Constrants::Menu::MENU_WINDOW);
    menu = window_menu->menu();
    menu->setTitle(tr("&Window"));
    menu_bar_container->addMenu(window_menu);

    ActionContainer *perspective_menu = ActionManager::createMenu(Constrants::Menu::MENU_PERSPECTIVE);
    menu = perspective_menu->menu();
    menu->setTitle(tr("&Perspectives"));
    window_menu->addMenu(perspective_menu);

    ActionContainer *window_view_menu = ActionManager::createMenu(Constrants::Menu::Window::MENU_VIEW);
    menu = window_view_menu->menu();
    menu->setTitle(tr("Show view"));
    window_menu->addMenu(window_view_menu);

    ActionContainer *help_menu = ActionManager::createMenu(Constrants::Menu::MENU_HELP);
    menu = help_menu->menu();
    menu->setTitle(tr("&Help"));

    menu_bar_container->addMenu(help_menu);

    ActionManager::createGroupAction(Constrants::ActionGruop::ACTION_GROUP_PERSPECTIVE);
}

void MainWindow::registerMainActions()
{
    Action *action = nullptr;

    ActionContainer *file_menu_container = ActionManager::actionContainer(Constrants::Menu::MENU_FILE);
    ActionContainer *help_menu_container = ActionManager::actionContainer(Constrants::Menu::MENU_HELP);

    exit_action_ = new QAction{tr("Quit"), this};
    action = ActionManager::registerAction(exit_action_, Constrants::Action::ACTION_EXIT);
    connect(exit_action_, &QAction::triggered, this, &QMainWindow::close);
    file_menu_container->addAction(action);

    about_action_ = new QAction{tr("About"), this};
    action = ActionManager::registerAction(about_action_, Constrants::Action::ACTION_ABOUT);
    help_menu_container->addAction(action);

}

void MainWindow::loadPerspectives()
{
    PerspectiveManager::loadPerspectives();

    ActionContainer *perspective_container = ActionManager::actionContainer(Core::Constrants::ActionGruop::ACTION_GROUP_PERSPECTIVE);

    // unregister actions
    QMapIterator<QString, Action*> i(perspective_container->actionMap());
    while(i.hasNext())
    {
        i.next();
        ActionManager::unregisterAction(i.key());
    }
    // clear GroupActionContainer
    perspective_container->clear();

    // TODO: remove actions
//    while(!perspective_action_list_.isEmpty())
//    {
//        QAction* action = perspective_action_list_.first();
//        perspective_action_list_.pop_front();
//        delete action;
//    }

    // add perspective tool bar and menu
    ActionContainer *perspective_menu = ActionManager::actionContainer(Constrants::Menu::MENU_PERSPECTIVE);
    foreach(IPerspective* pers, PerspectiveManager::perspectiveList())
    {
        QAction* action = new QAction(pers->displayName());
        action->setCheckable(true);
        action->setData(QVariant(pers->id()));

        Action* perspective_action = ActionManager::registerAction(action, Core::Constrants::Action::ACTION_PERSPECTIVE_PREFIX + "." + pers->id());
        perspective_container->addAction(perspective_action);

        perspective_menu->addAction(perspective_action);
    }

    foreach(Action* action, perspective_container->actionMap())
    {
        perspective_tool_bar_->addAction(action->action());
    }
    connect(perspective_container->actionGroup(), &QActionGroup::triggered, this, &MainWindow::slotPerspectiveActionTriggered);

}

void MainWindow::loadViews()
{
    ActionContainer *window_view_menu_container = ActionManager::actionContainer(Constrants::Menu::Window::MENU_VIEW);

    QList<DockView*> dock_view_list = PluginManager::getObjects<DockView>();
    foreach(DockView *dock_view, dock_view_list)
    {
        ViewSpec *view_spec = dock_view->viewSpec();
        qDebug()<<"[MainWindow::loadViews]"<<view_spec->id();

        QAction *view_action = new QAction{view_spec->name(), this};
        view_action->setIcon(QIcon(view_spec->iconLocation()));
        Action *action_container = ActionManager::registerAction(view_action, Constrants::Action::ACTION_VIEW_PREFIX + "." + view_spec->id());
        connect(view_action, &QAction::triggered, [=](bool){
            dock_view->dockWidget()->show();

            ConsoleDockWidget::info(ConsoleDockWidget::GeneralPanelId, "View::action triggerd: "+action_container->id());

        });
        window_view_menu_container->addAction(action_container);

        addDockWidget(dock_view->dockLocation(), dock_view->dockWidget());
    }
}

void MainWindow::activatePerspective(QString id)
{
    Action *action = ActionManager::action(Core::Constrants::Action::ACTION_PERSPECTIVE_PREFIX + "." + id);

    if(!action)
    {
        qWarning()<<"[MainWindow::activatePerspective] can't find perspective "<<id;
        return;
    }

    QAction *active_action = action->action();
    active_action->setChecked(true);

    //NOTE: action的setChecked不触发QActionGroup的triggered信号，所以强制执行该slot
    slotActivatePerspective(id);
}

void MainWindow::initStatusBar()
{
    QStatusBar *bar = statusBar();
    QSplitter *splitter = new QSplitter{Qt::Horizontal, bar};
    bar->insertPermanentWidget(0, splitter, 10);
    bar->addPermanentWidget(ProgressManager::statusBarWidget());
}
