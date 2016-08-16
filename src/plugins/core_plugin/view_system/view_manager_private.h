#pragma once

#include <QObject>
#include <QHash>
#include <QMap>

namespace Core{

namespace ViewSystem{

class ViewManager;
class ViewSpec;

class ViewManagerPrivate : public QObject
{
    Q_OBJECT
public:
    ViewManagerPrivate(ViewManager *parent = nullptr);

    ~ViewManagerPrivate();

    bool addView(ViewSpec *view_spec);

    QHash<QString, ViewSpec *> viewList();

private:
    QHash<QString, ViewSpec*> view_spec_list_;
    QMap<QString, ViewSpec *> path_to_view_spec_map_;

    ViewManager *q;

    friend class Core::ViewSystem::ViewManager;
};

}

}
