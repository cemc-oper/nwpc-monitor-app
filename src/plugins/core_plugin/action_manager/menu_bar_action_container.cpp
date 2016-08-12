#include "menu_bar_action_container.h"

#include <QMenuBar>
#include <QtDebug>

using namespace Core;

MenuBarActionContainer::MenuBarActionContainer(QString id, QObject *parent) :
    ActionContainer{id, parent},
    menu_bar_{0}
{

}

MenuBarActionContainer::~MenuBarActionContainer()
{
    qDebug()<<"[MenuBarActionContainer::~MenuBarActionContainer]";
}

void MenuBarActionContainer::setMenuBar(QMenuBar *menu_bar)
{
    menu_bar_ = menu_bar;
}

QMenuBar *MenuBarActionContainer::menuBar() const
{
    return menu_bar_;
}

void MenuBarActionContainer::insertAction(QAction *before, QAction *action)
{
    menu_bar_->insertAction(before, action);
}

void MenuBarActionContainer::insertMenu(QAction *before, QMenu *menu)
{
    menu_bar_->insertMenu(before, menu);
}

void MenuBarActionContainer::removeAction(QAction *action)
{
    menu_bar_->removeAction(action);
}

void MenuBarActionContainer::removeMenu(QMenu *menu)
{
    menu_bar_->removeAction(menu->menuAction());
}

bool MenuBarActionContainer::canBeAddedToMenu() const
{
    return false;
}
