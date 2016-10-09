#include "session.h"

#include <exception>
#include <QJsonValue>

using namespace Core::SessionSystem;
using namespace std;

Session::Session()
{

}

Session::Session(const QString &name, const QString &host, const QString &port, const QString &user, const QString &password):
    name_{name},
    host_{host},
    port_{port},
    user_{user},
    password_{password}
{

}

Session::Session(const QJsonObject &obj)
{
    if(!obj.contains("name"))
    {
        throw invalid_argument{"json object doesn't have key 'name'."};
    }
    name_ = obj["name"].toString();

    if(!obj.contains("connection"))
    {
        throw invalid_argument{"json object doesn't have key 'connection'."};
    }
    QJsonObject connection = obj["connection"].toObject();
    if(connection.isEmpty())
    {
        throw invalid_argument{"key 'connection' must be an object."};
    }

    if(!connection.contains("host"))
    {
        throw invalid_argument{"json object doesn't have key 'host'."};
    }
    host_ = connection["host"].toString();

    if(!connection.contains("port"))
    {
        throw invalid_argument{"json object doesn't have key 'port'."};
    }
    port_ = connection["port"].toString();

    if(!connection.contains("auth"))
    {
        throw invalid_argument{"connection doesn't have key 'auth'."};
    }
    QJsonObject auth = connection["auth"].toObject();
    if(auth.isEmpty())
    {
        throw invalid_argument{"key 'auth' must be an object."};
    }

    if(!auth.contains("user"))
    {
        throw invalid_argument{"json object doesn't have key 'user'."};
    }
    user_ = auth["user"].toString();;

    if(!auth.contains("password"))
    {
        throw invalid_argument{"json object doesn't have key 'password'."};
    }
    password_ = auth["password"].toString();;
}

bool Session::operator ==(const Session &other) const
{
    if(name_ != other.name_)
        return false;
    if(host_ != other.host_)
        return false;
    if(port_ != other.port_)
        return false;
    if(user_ != other.user_)
        return false;
    if(password_ != other.password_)
        return false;
    return true;
}

bool Session::isEmpty() const
{
    bool has_empty = host_.isEmpty()
            || port_.isEmpty()
            || user_.isEmpty()
            || password_.isEmpty();
    return has_empty;
}

QMap<QString, QString> Session::toArguments() const
{
    QMap<QString, QString> args;
    args["host"] = host_;
    args["port"] = port_;
    args["user"] = user_;
    args["password"] = password_;
    return args;
}
