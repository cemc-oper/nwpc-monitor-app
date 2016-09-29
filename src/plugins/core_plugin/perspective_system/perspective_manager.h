#pragma once

#include "../core_plugin_global.h"

#include <QObject>
#include <QVector>

namespace Core{

class CorePlugin;
class MainWindow;

namespace PerspectiveSystem{

class IPerspective;

class CORE_PLUGIN_EXPORT PerspectiveManager : public QObject
{
    Q_OBJECT
public:
    static PerspectiveManager *instance();

    static QVector<IPerspective *> perspectiveList();
    static int perspectiveIndex(QString id);
    static IPerspective *perspective(QString id);

    static void loadPerspectives();
    static void addPerspective(IPerspective *persp);    
    static void activatePerspective(const QString &id);

signals:

public slots:

private:
    explicit PerspectiveManager(QPointer<MainWindow> main_window, QObject *parent = 0);
    ~PerspectiveManager();

    friend class Core::CorePlugin;

};

}

}
