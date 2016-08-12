#include "action.h"

#include <QAction>

using namespace Core;

Action::Action(QString id, QObject *parent) :
    QObject{parent},
    id_{id},
    action_{new QAction(this)}
{

}

Action::~Action()
{
    action_->deleteLater();
}

QString Action::id() const
{
    return id_;
}

QAction *Action::action() const
{
    return action_;
}

void Action::setAction(QAction *action)
{
    action_ = action;
}
