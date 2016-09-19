#include "session_manager.h"

using namespace Core::SessionSystem;

SessionManager::SessionManager(QObject *parent) : QObject(parent)
{

}

void SessionManager::addSession(const Session &session)
{
    session_map_[session.name_] = session;
}

bool SessionManager::containSession(const QString &name) const
{
    return session_map_.contains(name);
}

Session SessionManager::getSession(const QString &name)
{
    if(containSession(name))
        return session_map_[name];
    else
        return Session{};
}

void SessionManager::removeSession(const QString &name)
{
    if(containSession(name))
        session_map_.remove(name);
}

int SessionManager::sessionCount() const
{
    return session_map_.size();
}

QMap<QString, Session> &SessionManager::sessionMap()
{
    return session_map_;
}
