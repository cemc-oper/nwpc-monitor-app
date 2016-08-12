#pragma once

#include <core_plugin_global.h>

#include <QObject>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
class QMenu;
class QMenuBar;
class QAction;
QT_END_NAMESPACE

namespace Core{

class Action;

struct ActionGroup{
    ActionGroup(QString id) : id_{id}{}
    QString id_;
    QList<QObject *> items_;
};

class CORE_PLUGIN_EXPORT ActionContainer : public QObject
{
    Q_OBJECT
public:
    explicit ActionContainer(QString id, QObject *parent = 0);

    ~ActionContainer();

    virtual QString id() const;

    virtual QMenu *menu() const;

    virtual QMenuBar *menuBar() const;


    virtual void addAction(Action *action);
    virtual void addMenu(ActionContainer* menu);
    virtual Action *addSeparator();


    virtual void insertAction(QAction *before, QAction *action) = 0;
    virtual void insertMenu(QAction *before, QMenu *menu) = 0;

    virtual void removeAction(QAction *action) = 0;
    virtual void removeMenu(QMenu *menu) = 0;

    virtual void clear();

signals:

public slots:

protected:
    virtual bool canBeAddedToMenu() const = 0;

    QString id_;
};

}
