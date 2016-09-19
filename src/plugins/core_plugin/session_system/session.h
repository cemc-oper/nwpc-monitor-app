#pragma once

#include "../core_plugin_global.h"

#include <QString>

namespace Core{

namespace SessionSystem{

class CORE_PLUGIN_EXPORT Session
{
public:
    explicit Session(const QString &name, const QString &host, const QString &port, const QString &user, const QString &password);

public:
    QString name_;
    QString host_;
    QString port_;
    QString user_;
    QString password_;
};

}

}
