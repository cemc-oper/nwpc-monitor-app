#pragma once

#include "../core_plugin_global.h"

#include <QString>
#include <QJsonObject>
#include <QMap>

namespace Core{

namespace SessionSystem{

class CORE_PLUGIN_EXPORT Session
{
public:
    Session();
    Session(const QString &name, const QString &host, const QString &port, const QString &user, const QString &password);
    explicit Session(const QJsonObject &obj);

    bool operator ==(const Session &other) const;
    bool isEmpty() const;

    QMap<QString, QString> toArguments() const;

public:
    QString name_;
    QString host_;
    QString port_;
    QString user_;
    QString password_;
};

}

}
