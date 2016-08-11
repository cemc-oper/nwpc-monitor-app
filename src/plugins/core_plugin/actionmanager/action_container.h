#pragma once

#include <QObject>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
class QMenu;
class QMenuBar;
class QAction;
QT_END_NAMESPACE

namespace Core{

struct ActionGroup{
    ActionGroup(QString id) : id_{id}{}
    QString id_;
    QList<QObject *> items_;
};

class ActionContainer : public QObject
{
    Q_OBJECT
public:
    explicit ActionContainer(QString id, QObject *parent = 0);

    ~ActionContainer();

    virtual QString id() const;

    virtual QMenu *menu() const;

    virtual QMenuBar *menuBar() const;


    virtual void addAction(QAction *action);

    virtual void addMenu(ActionContainer* menu);

    virtual void addSeparator();


    virtual void insertAction(QAction *before, QAction *action) = 0;
    virtual void insertMenu(QAction *before, QMenu *menu) = 0;

    virtual void removeAction(QAction *action) = 0;
    virtual void removeMenu(QMenu *menu) = 0;

signals:

public slots:

protected:
    virtual bool canBeAddedToMenu() const = 0;

    QString id_;
};

}
