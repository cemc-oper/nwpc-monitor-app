#include "welcome_widget.h"
#include "ui_welcome_widget.h"

#include <core_plugin/perspective_system/perspective_manager.h>

using namespace Core;
using namespace Welcome;

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);
    connect(ui->startup_loadleveler_monitor_button, &QPushButton::clicked, [=](){
         PerspectiveSystem::PerspectiveManager::activatePerspective("loadleveler_monitor");
    });
    connect(ui->startup_sms_monitor_button, &QPushButton::clicked, [=](){
         PerspectiveSystem::PerspectiveManager::activatePerspective("sms_monitor");
    });
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
