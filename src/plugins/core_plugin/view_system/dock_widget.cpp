#include "dock_widget.h"

using namespace Core::ViewSystem;

DockWidget::DockWidget(QString id, QString name, QStringList path_list, QString icon_location, Qt::DockWidgetArea dock_location, QWidget *parent):
    QDockWidget{parent},
    kId{id},
    kName{name},
    kPathList{path_list},
    kIconLocation{icon_location},
    kDockLocation{dock_location}
{

}
