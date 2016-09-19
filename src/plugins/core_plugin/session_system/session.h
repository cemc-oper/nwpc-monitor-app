#pragma once

#include "../core_plugin_global.h"

#include <QString>
#include <QJsonObject>

namespace Core{

namespace SessionSystem{

class CORE_PLUGIN_EXPORT Session
{
public:
    Session();
    Session(const QString &name, const QString &host, const QString &port, const QString &user, const QString &password);
    explicit Session(const QJsonObject &obj);

    bool operator ==(const Session &other) const;

public:
    QString name_;
    QString host_;
    QString port_;
    QString user_;
    QString password_;
};

}

}
