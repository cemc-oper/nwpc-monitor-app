#include "action_container.h"
#include "action.h"
#include "action_manager.h"
#include "menu_action_container.h"

#include <QAction>
#include <QtDebug>

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

QActionGroup *ActionContainer::actionGroup() const
{
    return nullptr;
}

QList<Action *> ActionContainer::actionList() const
{
    return QList<Action *>();
}

void ActionContainer::addAction(Action *action)
{
    insertAction(0, action->action());
}

void ActionContainer::addMenu(ActionContainer *menu)
{
    if(!menu->canBeAddedToMenu())
        return;
    MenuActionContainer *container = static_cast<MenuActionContainer *>(menu);
    QMenu *m = container->menu();
    qDebug()<<"[ActionContainer::addMenu] menu:"<<m;
    insertMenu(0, m);
}

Action *ActionContainer::addSeparator()
{
    static int separtor_id_count = 0;
    QAction *separator = new QAction(this);
    separator->setSeparator(true);

    QString separator_id = "Separator." + QString::number(++separtor_id_count);

    Action *separator_action = ActionManager::registerAction(separator, separator_id);
    addAction(separator_action);

    return separator_action;
}

void ActionContainer::clear()
{
    //TODO: 需要清除对象
}
