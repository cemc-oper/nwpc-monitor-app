#include "group_action_container.h"
#include "action.h"

#include <QActionGroup>
#include <QtDebug>

using namespace Core;

GroupActionContainer::GroupActionContainer(QString id, QObject *parent) :
    ActionContainer{id, parent},
    action_group_{new QActionGroup{this}}
{

}

QActionGroup *GroupActionContainer::actionGroup() const
{
    return action_group_;
}

QMap<QString, Action *> GroupActionContainer::actionMap() const
{
    return action_map_;
}

void GroupActionContainer::addAction(Action *action)
{
    action_map_[action->id()] = action;
    ActionContainer::addAction(action);
}

void GroupActionContainer::insertAction(QAction *before, QAction *action)
{
    Q_UNUSED(before);
    action_group_->addAction(action);
}

void GroupActionContainer::insertMenu(QAction *before, QMenu *menu)
{
    Q_UNUSED(before);
    Q_UNUSED(menu);
    qWarning()<<"[GroupActionContainer::insertMenu] GroupActionContainer don't support menu.";
    return;
}

void GroupActionContainer::removeAction(QAction *action)
{
    action_group_->removeAction(action);
}

void GroupActionContainer::removeMenu(QMenu *menu)
{
    Q_UNUSED(menu);
    qWarning()<<"[GroupActionContainer::removeMenu] GroupActionContainer don't support menu.";
    return;
}

void GroupActionContainer::clear()
{
    foreach(Action *action, action_map_)
    {
        action_group_->removeAction(action->action());
        action->deleteLater();
    }
    action_map_.clear();

    ActionContainer::clear();
}

bool GroupActionContainer::canBeAddedToMenu() const
{
    return true;
}
