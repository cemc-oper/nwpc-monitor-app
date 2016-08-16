#pragma once

#include "view_system/dock_widget.h"

#include <QStringList>
#include <QString>

namespace Core{

namespace Views{

namespace Ui {
class OutputDockWidget;
}

class OutputDockWidget : public Core::ViewSystem::DockWidget
{
    Q_OBJECT

public:
    explicit OutputDockWidget(QWidget *parent = 0);
    ~OutputDockWidget();

    void appendText(const QString &text);

public:
    const QString Id {"NwpcMonitor.CorePlugin.View.OutputDockView"};
    const QString Name {"Output"};
    const QStringList PathList {QStringList()<<"General"<<"Output"};

    const Qt::DockWidgetArea DockLocation {Qt::BottomDockWidgetArea};

private:
    Ui::OutputDockWidget *ui;
};

}

}
