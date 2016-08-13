#include "view_manager_private.h"

#include "view_manager.h"
#include "view_spec.h"

using namespace Core::ViewSystem;

ViewManagerPrivate::ViewManagerPrivate(ViewManager *parent):
    QObject{parent},
    q(parent)
{

}

ViewManagerPrivate::~ViewManagerPrivate()
{

}

bool ViewManagerPrivate::addView(ViewSpec *view_spec)
{
    view_spec_list_[view_spec->id()] = view_spec;
    return true;
}

QHash<QString, ViewSpec *> ViewManagerPrivate::viewList()
{
    return view_spec_list_;
}
