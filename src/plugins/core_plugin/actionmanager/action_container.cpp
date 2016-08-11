#include "action_container.h"

#include <QAction>

using namespace Core;

ActionContainer::ActionContainer(QString id, QObject *parent) :
    QObject{parent},
    id_{id}
{

}

ActionContainer::~ActionContainer()
{

}

QString ActionContainer::id() const
{
    return id_;
}

QMenu *ActionContainer::menu() const
{
    return nullptr;
}

QMenuBar *ActionContainer::menuBar() const
{
    return nullptr;
}

void ActionContainer::addAction(QAction *action)
{
    insertAction(0, action);
}

void ActionContainer::addMenu(ActionContainer *menu)
{
    if(!menu->canBeAddedToMenu())
        return;
    insertMenu(0, menu->menu());
}

void ActionContainer::addSeparator()
{
    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    addAction(separator);
}
