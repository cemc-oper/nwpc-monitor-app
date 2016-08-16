#pragma once

#include <core_plugin_global.h>

#include <QObject>
#include <QHash>

namespace Core{

class CorePlugin;

namespace ViewSystem{

class ViewSpec;

class ViewManager : public QObject
{
    Q_OBJECT
public:
    static ViewManager *instance();

    static bool addView(ViewSpec *view_spec);
    static QHash<QString, ViewSpec *> viewList();

    static ViewSpec *viewSpecFromPath(const QString path);

signals:

public slots:

private:
    explicit ViewManager(QObject *parent = 0);
    ~ViewManager();

    friend class Core::CorePlugin;
};

}

}
