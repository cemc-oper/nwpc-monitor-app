#pragma once

#include <QObject>
#include <QHash>

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
    ViewManager *q;

    friend class Core::ViewSystem::ViewManager;
};

}

}
