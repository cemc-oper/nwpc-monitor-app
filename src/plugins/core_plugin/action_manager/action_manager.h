#pragma once

#include <core_plugin_global.h>

#include <QObject>
#include <QHash>

QT_BEGIN_NAMESPACE
class QAction;
class QMenuBar;
QT_END_NAMESPACE

namespace Core{

class Action;
class ActionContainer;
class CorePlugin;

class CORE_PLUGIN_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public:

    static ActionManager *instance();

    static ActionContainer *createMenuBar(QString id);
    static ActionContainer *createMenu(QString id);
    static ActionContainer *createGroupAction(QString id);

    static Action *registerAction(QAction *action, QString id);
    static void unregisterAction(QString id);

    static Action *action(QString id);
    static ActionContainer *actionContainer(QString id);

signals:

public slots:
    void containerDestroyed();

private:
    explicit ActionManager(QObject *parent = 0);

    ~ActionManager();

    friend class Core::CorePlugin;

    QHash<QString, ActionContainer *> id_to_container_map_;
    QHash<QString, Action *> id_to_action_map_;
};

}
