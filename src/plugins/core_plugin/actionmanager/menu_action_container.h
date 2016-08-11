#pragma once

#include "action_container.h"

#include <QPointer>

namespace Core{


class MenuActionContainer : public ActionContainer
{
    Q_OBJECT
public:
    MenuActionContainer(QString id, QObject *parent=0);

    ~MenuActionContainer();

    QMenu *menu() const;

    void insertAction(QAction *before, QAction *action);
    void insertMenu(QAction *before, QMenu *menu);

    void removeAction(QAction *action);
    void removeMenu(QMenu *menu);

protected:
    bool canBeAddedToMenu() const override;

private:
    QPointer<QMenu> menu_;
};

}
