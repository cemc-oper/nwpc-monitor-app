#pragma once

#include <QObject>
#include <QVector>

namespace Core{

namespace PerspectiveSystem{

class PerspectiveManager;
class IPerspective;

class PerspectiveManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit PerspectiveManagerPrivate(PerspectiveManager *parent = nullptr);

    ~PerspectiveManagerPrivate();

    QVector<IPerspective *> perspectiveList();

    void addPerspective(IPerspective *persp);

signals:

public slots:

private:
    PerspectiveManager *q;

    QVector<IPerspective*> perspective_list_;

    friend class Core::PerspectiveSystem::PerspectiveManager;
};

}
}
