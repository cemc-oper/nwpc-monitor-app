#include "view_manager.h"
#include "view_manager_private.h"

using namespace Core;
using namespace Core::ViewSystem;

ViewManager *view_manager_instance = nullptr;
ViewManagerPrivate *d = nullptr;

ViewManager *ViewManager::instance()
{
    return view_manager_instance;
}

bool ViewManager::addView(ViewSpec *view_spec)
{
    return d->addView(view_spec);
}

QHash<QString, ViewSpec *> ViewManager::viewList()
{
    return d->viewList();
}

ViewSpec *ViewManager::viewSpecFromPath(const QString path)
{
    if(d->path_to_view_spec_map_.contains(path))
    {
        return d->path_to_view_spec_map_[path];
    }
    else
    {
        return nullptr;
    }
}

ViewManager::ViewManager(QObject *parent) : QObject(parent)
{
    view_manager_instance = this;
    d = new ViewManagerPrivate{this};
}

ViewManager::~ViewManager()
{
    view_manager_instance = nullptr;
    d->deleteLater();
    d = nullptr;
}
