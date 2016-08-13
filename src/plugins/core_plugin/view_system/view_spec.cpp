#include "view_spec.h"

#include "iview.h"

using namespace Core::ViewSystem;

ViewSpec::ViewSpec(QObject *parent) :
    QObject{parent},
    view_{nullptr}
{

}

ViewSpec::~ViewSpec()
{

}

PluginSystem::PluginSpec *ViewSpec::pluginSpec() const
{
    return plugin_spec_;
}

void ViewSpec::setPluginSpec(PluginSystem::PluginSpec *plugin_spec)
{
    plugin_spec_ = plugin_spec;
}

QString ViewSpec::id() const
{
    return id_;
}

void ViewSpec::setId(const QString &id)
{
    id_ = id;
}

QString ViewSpec::name() const
{
    return name_;
}

void ViewSpec::setName(const QString &name)
{
    name_ = name;
}

QStringList ViewSpec::path() const
{
    return path_list_;
}

void ViewSpec::setPath(const QStringList &path)
{
    path_list_ = path;
}

IView *ViewSpec::view()
{
    return view_;
}

void ViewSpec::setView(IView *view)
{
    view_ = view;
    view_->view_spec_ = this;
}

