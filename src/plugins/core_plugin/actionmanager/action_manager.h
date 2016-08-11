#pragma once

#include <QObject>
#include <QHash>

namespace Core{

class ActionContainer;


class ActionManager : public QObject
{
    Q_OBJECT
public:
    explicit ActionManager(QObject *parent = 0);

    ~ActionManager();

    static ActionManager *instance();

    static ActionContainer *createMenuBar(QString id);

    static ActionContainer *createMenu(QString id);

    static ActionContainer *actionContainer(QString id);

signals:

public slots:
    void containerDestroyed();

private:
    QHash<QString, ActionContainer*> id_to_container_map_;
};

}
