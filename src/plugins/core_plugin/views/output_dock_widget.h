#pragma once

#include "view_system/dock_widget.h"

#include <QStringList>
#include <QString>

QT_BEGIN_NAMESPACE
class QToolBar;
QT_END_NAMESPACE

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

private:
    void setupActions();
    void setupToolBar();

    Ui::OutputDockWidget *ui;
    QToolBar *tool_bar_;


public:
    const QString Id {"NwpcMonitor.CorePlugin.View.OutputDockView"};
    const QString Name {"Output"};
    const QStringList PathList {QStringList()<<"General"<<"Output"};

    const Qt::DockWidgetArea DockLocation{Qt::BottomDockWidgetArea};

};

}

}
