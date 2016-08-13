#pragma once

#include <QObject>

namespace Core{

namespace ViewSystem{

class ViewSpec;

class IView : public QObject
{
    Q_OBJECT
public:
    explicit IView(QObject *parent = nullptr);
    ~IView();

    ViewSpec *viewSpec();

signals:

public slots:

protected:
    ViewSpec *view_spec_;

    friend class Core::ViewSystem::ViewSpec;
};

}

}
