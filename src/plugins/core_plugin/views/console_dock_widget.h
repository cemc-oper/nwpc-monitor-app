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
class ConsoleDockWidget;
}

const QString GeneralPanelId {"General"};

class ConsoleDockWidget : public Core::ViewSystem::DockWidget
{
    Q_OBJECT

public:    
    explicit ConsoleDockWidget(QWidget *parent = 0);
    ~ConsoleDockWidget();

    void appendText(const QString &text);

    void appendInfo(const QString &text);
    void appendWarning(const QString &text);
    void appendError(const QString &text);

    static void info(const QString &output_id, const QString &text);
    static void warning(const QString &output_id, const QString &text);
    static void error(const QString &output_id, const QString &text);

    static ConsoleDockWidget *outputDockWidget(const QString &output_panel_id = ConsoleDockWidget::GeneralPanelId);

private slots:
    void slotScrollToEnd(bool flag);
    void slotScroolToEnd();

private:
    void setupActions();
    void setupToolBar();

    Ui::ConsoleDockWidget *ui;
    QToolBar *tool_bar_;

public:
    static const QString GeneralPanelId;
};

}

}
