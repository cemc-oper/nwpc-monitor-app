#pragma once

#include "perspective_system/iperspective.h"

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
class QToolBar;
class QAction;
QT_END_NAMESPACE

namespace Core{

namespace Ui {
class MainWindow;
}

using Core::PerspectiveSystem::IPerspective;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initialize();
    void pluginsInitialized();
    void aboutToShutdown();

public slots:
    void slotPerspectiveActionTriggered(QAction* action);

private slots:
    void slotActivatePerspective(QString id);

private:
    void registerMainActionContainers();
    void registerMainActions();

    void loadPerspectives();
    void loadViews();
    void activatePerspective(QString id);
    void initStatusBar();

    Ui::MainWindow *ui;

    QToolBar* perspective_tool_bar_;

    QAction *exit_action_;
    QAction *about_action_;
};

}
