#include "perspective_manager.h"
#include "perspective_manager_private.h"

#include "../mainwindow.h"

using namespace Core::PerspectiveSystem;

PerspectiveManager *perspective_manager_instance = nullptr;
PerspectiveManagerPrivate *d = nullptr;

PerspectiveManager *PerspectiveManager::instance()
{
    return perspective_manager_instance;
}

QVector<IPerspective *> PerspectiveManager::perspectiveList()
{
    return d->perspectiveList();
}

int PerspectiveManager::perspectiveIndex(QString id)
{
    return d->perspectiveIndex(id);
}

IPerspective *PerspectiveManager::perspective(QString id)
{
    return d->perspective(id);
}

void PerspectiveManager::loadPerspectives()
{
    d->loadPerspectives();
}

void PerspectiveManager::addPerspective(IPerspective *persp)
{
    d->addPerspective(persp);
}

void PerspectiveManager::activatePerspective(const QString &id)
{
    d->activatePerspective(id);
}

PerspectiveManager::PerspectiveManager(QPointer<Core::MainWindow> main_window, QObject *parent) : QObject(parent)
{
    perspective_manager_instance = this;
    d = new PerspectiveManagerPrivate{main_window, this};
}

PerspectiveManager::~PerspectiveManager()
{

}
