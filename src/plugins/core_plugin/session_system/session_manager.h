#pragma once

#include "session.h"
#include "../core_plugin_global.h"

#include <QObject>
#include <QMap>

namespace Core{

namespace SessionSystem{

class CORE_PLUGIN_EXPORT SessionManager : public QObject
{
    Q_OBJECT
public:
    explicit SessionManager(QObject *parent = 0);

    void addSession(const Session &session);
    bool containSession(const QString &name) const;
    Session getSession(const QString &name);
    void removeSession(const QString &name);

    int sessionCount() const;

    QMap<QString, Session> &sessionMap();

signals:

public slots:

private:
    QMap<QString, Session> session_map_;
};

}

}
