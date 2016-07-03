#pragma once

#include "iperspective.h"

namespace Core{

class WelcomeWidget;

class CORE_PLUGIN_EXPORT WelcomePerspective : public IPerspective
{
    Q_OBJECT
public:
    explicit WelcomePerspective(QObject *parent = 0);

    ~WelcomePerspective();

private:
    WelcomeWidget* welcome_widget_;
};

}
