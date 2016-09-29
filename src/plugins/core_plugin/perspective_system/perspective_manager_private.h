#pragma once

#include <QObject>
#include <QVector>
#include <QPointer>

namespace Core{

class MainWindow;

namespace PerspectiveSystem{

class PerspectiveManager;
class IPerspective;

class PerspectiveManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit PerspectiveManagerPrivate(QPointer<Core::MainWindow> main_window, PerspectiveManager *parent = nullptr);

    ~PerspectiveManagerPrivate();

    QVector<IPerspective *> perspectiveList();
    int perspectiveIndex(QString id);
    IPerspective *perspective(QString id);

    void loadPerspectives();
    void addPerspective(IPerspective *persp);
    void activatePerspective(const QString &id);

signals:

public slots:

private:
    PerspectiveManager *q;

    QVector<IPerspective*> perspective_list_;
    QPointer<Core::MainWindow> main_window_;

    friend class Core::PerspectiveSystem::PerspectiveManager;
};

}
}
