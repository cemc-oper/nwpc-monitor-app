#pragma once

#include "iview.h"

#include <QObject>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QDockWidget;
QT_END_NAMESPACE

namespace Core{

namespace ViewSystem{

class DockView : public IView
{
    Q_OBJECT
public:
    explicit DockView(QObject *parent = 0);

    QDockWidget *dockWidget() const;
    void setDockWidget(QDockWidget *dock_widget);

signals:

public slots:

protected:
    QPointer<QDockWidget> dock_widget_;
};

}

}
