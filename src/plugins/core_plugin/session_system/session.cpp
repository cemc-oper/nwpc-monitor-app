#include "session.h"

using namespace Core::SessionSystem;


Session::Session(const QString &name, const QString &host, const QString &port, const QString &user, const QString &password):
    name_{name},
    host_{host},
    port_{port},
    user_{user},
    password_{password}
{

}
