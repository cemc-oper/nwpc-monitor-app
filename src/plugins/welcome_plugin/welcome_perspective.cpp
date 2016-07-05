#include "welcome_perspective.h"

#include "welcome_widget.h"

using namespace Welcome;
using namespace Core;

WelcomePerspective::WelcomePerspective(QObject *parent):
    IPerspective(parent)
{
    setDisplayName("Welcome");
    setId("welcome");

    welcome_widget_ = new WelcomeWidget();
    setWidget(welcome_widget_);
}

WelcomePerspective::~WelcomePerspective()
{
    delete welcome_widget_;
    welcome_widget_ = 0;
}
