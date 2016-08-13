#include "dock_view.h"

#include <QDockWidget>

using namespace Core::ViewSystem;

DockView::DockView(QObject *parent) :
    IView{parent}
{

}

QDockWidget *DockView::dockWidget() const
{
    return dock_widget_;
}

void DockView::setDockWidget(QDockWidget *dock_widget)
{
    dock_widget_ = dock_widget;
}
