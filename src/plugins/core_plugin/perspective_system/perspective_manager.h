#pragma once

#include <core_plugin_global.h>

#include <QObject>
#include <QVector>

namespace Core{

class CorePlugin;

namespace PerspectiveSystem{

class IPerspective;

class CORE_PLUGIN_EXPORT PerspectiveManager : public QObject
{
    Q_OBJECT
public:
    static PerspectiveManager *instance();

    static QVector<IPerspective *> perspectiveList();

    static void addPerspective(IPerspective *persp);

signals:

public slots:

private:
    explicit PerspectiveManager(QObject *parent = 0);
    ~PerspectiveManager();

    friend class Core::CorePlugin;

};

}

}
