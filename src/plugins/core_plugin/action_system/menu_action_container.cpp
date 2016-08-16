#include "menu_action_container.h"

#include <QMenu>

using namespace Core;

MenuActionContainer::MenuActionContainer(QString id, QObject *parent):
    ActionContainer{id, parent},
    menu_(new QMenu)
{
    menu_->setObjectName(id);
}

MenuActionContainer::~MenuActionContainer()
{
    delete menu_;
}

QMenu *MenuActionContainer::menu() const
{
    return menu_;
}

void MenuActionContainer::insertAction(QAction *before, QAction *action)
{
    menu_->insertAction(before, action);
}

void MenuActionContainer::insertMenu(QAction *before, QMenu *menu)
{
    menu_->insertMenu(before, menu);
}

void MenuActionContainer::removeAction(QAction *action)
{
    menu_->removeAction(action);
}

void MenuActionContainer::removeMenu(QMenu *menu)
{
    menu_->removeAction(menu->menuAction());
}

bool MenuActionContainer::canBeAddedToMenu() const
{
    return true;
}
