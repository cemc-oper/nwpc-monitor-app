#include "iperspective.h"

using namespace Core;

IPerspective::IPerspective(QObject *parent) : QObject(parent)
{

}

QString IPerspective::displayName() const
{
    return display_name_;
}

void IPerspective::setDisplayName(const QString &display_name)
{
    display_name_ = display_name;
}

QWidget *IPerspective::widget() const
{
    return widget_;
}

void IPerspective::setWidget(QWidget *widget)
{
    widget_ = widget;
}

QString IPerspective::id() const
{
    return id_;
}

void IPerspective::setId(const QString &id)
{
    id_ = id;
}
