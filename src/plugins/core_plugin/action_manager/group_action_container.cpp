#include "group_action_container.h"

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

QList<Action *> GroupActionContainer::actionList() const
{
    return action_list_;
}

void GroupActionContainer::addAction(Action *action)
{
    action_list_.append(action);
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
    action_list_.clear();
    action_group_.clear();
    ActionContainer::clear();
}

bool GroupActionContainer::canBeAddedToMenu() const
{
    return true;
}
