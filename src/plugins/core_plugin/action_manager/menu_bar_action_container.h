#pragma once

#include "action_container.h"

#include <QPointer>

namespace Core{

class MenuBarActionContainer : public ActionContainer
{
    Q_OBJECT
public:
    explicit MenuBarActionContainer(QString id, QObject *parent = 0);
    ~MenuBarActionContainer();

    void setMenuBar(QMenuBar *menuBar);
    QMenuBar *menuBar() const;

    void insertAction(QAction *before, QAction *action);
    void insertMenu(QAction *before, QMenu *menu);

    void removeAction(QAction *action);
    void removeMenu(QMenu *menu);

signals:

public slots:

protected:
    bool canBeAddedToMenu() const;

private:
    QMenuBar *menu_bar_;
};

}
