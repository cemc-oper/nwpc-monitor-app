#include "action_manager.h"
#include "action.h"
#include "menu_action_container.h"
#include "menu_bar_action_container.h"
#include "group_action_container.h"

#include <QMenuBar>
#include <QAction>
#include <QtDebug>

using namespace Core;

static ActionManager *action_manager = nullptr;

ActionManager::ActionManager(QObject *parent) :
    QObject{parent}
{
    action_manager = this;
}

ActionManager::~ActionManager()
{
    action_manager = nullptr;
}

ActionManager *ActionManager::instance()
{
    return action_manager;
}

ActionContainer *ActionManager::createMenuBar(QString id)
{
    const auto it = action_manager->id_to_container_map_.constFind(id);
    if (it != action_manager->id_to_container_map_.constEnd())
    {
        return it.value();
    }

    QMenuBar *menu_bar = new QMenuBar;
    menu_bar->setObjectName(id);

    MenuBarActionContainer *menu_bar_container = new MenuBarActionContainer(id);
    menu_bar_container->setMenuBar(menu_bar);

    action_manager->id_to_container_map_.insert(id, menu_bar_container);
    connect(menu_bar_container, &QObject::destroyed,
            action_manager, &ActionManager::containerDestroyed);

    return menu_bar_container;
}

ActionContainer *ActionManager::createMenu(QString id)
{
    const auto it = action_manager->id_to_container_map_.constFind(id);
    if (it !=  action_manager->id_to_container_map_.constEnd())
        return it.value();

    MenuActionContainer *menu_container = new MenuActionContainer(id);

    action_manager->id_to_container_map_.insert(id, menu_container);
    connect(menu_container, &QObject::destroyed, action_manager, &ActionManager::containerDestroyed);

    return menu_container;
}

ActionContainer *ActionManager::createGroupAction(QString id)
{
    const auto it = action_manager->id_to_container_map_.constFind(id);
    if (it !=  action_manager->id_to_container_map_.constEnd())
        return it.value();

    GroupActionContainer *group_container = new GroupActionContainer(id);

    action_manager->id_to_container_map_.insert(id, group_container);
    connect(group_container, &QObject::destroyed, action_manager, &ActionManager::containerDestroyed);

    return group_container;
}

Action *ActionManager::registerAction(QAction *action, QString id)
{
    Action *registed_action = action_manager->action(id);
    if(registed_action)
    {
        qWarning()<<"[ActionManager::registerAction] action is registed with id:"<<id;
        return registed_action;
    }

    Action *registing_action = new Action(id);
    registing_action->setAction(action);
    action_manager->id_to_action_map_.insert(id, registing_action);
    return registing_action;
}

void ActionManager::unregisterAction(QString id)
{

}

Action *ActionManager::action(QString id)
{
    ActionManager *a = action_manager;
    const auto it = action_manager->id_to_action_map_.constFind(id);
    if(it == action_manager->id_to_action_map_.constEnd())
    {
        //qWarning()<<"[ActionManager::action] faid to find:"<< id;
        return 0;
    }
    return it.value();
}

ActionContainer *ActionManager::actionContainer(QString id)
{
    const auto it = action_manager->id_to_container_map_.constFind(id);
    if (it == action_manager->id_to_container_map_.constEnd()) {
        qWarning() << "[ActionManager::actionContainer] failed to find :"
                   << id;
        return 0;
    }
    return it.value();
}

void ActionManager::containerDestroyed()
{
    ActionContainer *container = static_cast<ActionContainer *>(sender());
    id_to_container_map_.remove(id_to_container_map_.key(container));
}
