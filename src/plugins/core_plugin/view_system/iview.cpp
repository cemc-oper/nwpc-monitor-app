#include "iview.h"

#include "view_spec.h"

using namespace Core::ViewSystem;

IView::IView(QObject *parent) :
    QObject{parent},
    view_spec_{nullptr}
{

}

IView::~IView()
{

}

ViewSpec *IView::viewSpec()
{
    return view_spec_;
}
