#pragma once

#include "action_container.h"

#include <QPointer>
#include <QList>

QT_BEGIN_NAMESPACE
class QActionGroup;
QT_END_NAMESPACE

namespace Core{

class Action;

/**
 * @brief The GroupActionContainer class
 *
 * QActionGroup 的容器类
 */
class GroupActionContainer : public ActionContainer
{
public:
    GroupActionContainer(QString id, QObject *parent=0);

    QActionGroup *actionGroup() const override;
    QMap<QString, Action *> actionMap() const override;

    void addAction(Action *action) override;

    void insertAction(QAction *before, QAction *action) override;
    void insertMenu(QAction *before, QMenu *menu) override;

    void removeAction(QAction *action) override;
    void removeMenu(QMenu *menu) override;

    void clear() override;

signals:

public slots:

protected:
    bool canBeAddedToMenu() const override;

    QPointer<QActionGroup> action_group_;
    QMap<QString, Action *> action_map_;
};

}
