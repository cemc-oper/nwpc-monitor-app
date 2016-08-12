#pragma once

#include "iperspective.h"

#include <QMainWindow>
#include <QPointer>
#include <QVector>
#include <QMap>

QT_BEGIN_NAMESPACE
class QToolBar;
class QActionGroup;
class QAction;
class QSignalMapper;
QT_END_NAMESPACE

namespace Core{

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void loadPerspectives();

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
    QVector<QAction*> perspective_action_list_;
    QMap<QString, QAction*> perspective_id_to_action_map_;
    QActionGroup* perspective_action_group_;
    QSignalMapper* perspective_signal_mapper_;

    QPointer<QAction> exit_action;
    QPointer<QAction> about_action;
};

}
