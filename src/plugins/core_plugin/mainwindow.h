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

    void loadPerspectives();
    void loadViews();

    void activatePerspective(QString id);

public slots:
    void slotPerspectiveActionTriggered(QAction* action);

private slots:
    void slotActivatePerspective(QString id);

private:
    void addPerspective(IPerspective* perspective);
    int perspectiveIndex(QString id);

    void registerMainActionContainers();
    void registerMainActions();

    Ui::MainWindow *ui;

    QVector<IPerspective*> perspective_list_;

    QToolBar* perspective_tool_bar_;

    QAction *exit_action_;
    QAction *about_action_;
};

}
