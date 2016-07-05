#pragma once

#include "welcome_plugin_global.h"

#include <core_plugin/iperspective.h>

namespace Welcome{

class WelcomeWidget;

class WELCOME_PLUGIN_EXPORT WelcomePerspective : public Core::IPerspective
{
    Q_OBJECT
public:
    explicit WelcomePerspective(QObject *parent = 0);

    ~WelcomePerspective();

private:
    WelcomeWidget* welcome_widget_;
};

}
