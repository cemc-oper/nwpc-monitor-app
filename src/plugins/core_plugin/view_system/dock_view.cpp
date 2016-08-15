#include "dock_view.h"

#include <QDockWidget>

using namespace Core::ViewSystem;

DockView::DockView(QObject *parent) :
    IView{parent},
    dock_widget_{nullptr},
    dock_location_{Qt::BottomDockWidgetArea}
{

}

QDockWidget *DockView::dockWidget() const
{
    return dock_widget_;
}

void DockView::setDockWidget(QDockWidget *dock_widget)
{
//    if(dock_widget_)
//    {
//        disconnect(dock_widget_, &QDockWidget::dockLocationChanged, this, &DockView::slotSetDockLocation);
//    }
    dock_widget_ = dock_widget;
//    connect(dock_widget_, &QDockWidget::dockLocationChanged, this, &DockView::slotSetDockLocation);
}

void DockView::setInitDockLocation(Qt::DockWidgetArea dock_location)
{
    slotSetDockLocation(dock_location);
}

Qt::DockWidgetArea DockView::dockLocation() const
{
    return dock_location_;
}

void DockView::slotSetDockLocation(Qt::DockWidgetArea dock_location)
{
    dock_location_ = dock_location;
}
