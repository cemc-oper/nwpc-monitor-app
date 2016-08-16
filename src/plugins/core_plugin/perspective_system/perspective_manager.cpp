#include "perspective_manager.h"
#include "perspective_manager_private.h"

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

void PerspectiveManager::addPerspective(IPerspective *persp)
{
    d->addPerspective(persp);
}

PerspectiveManager::PerspectiveManager(QObject *parent) : QObject(parent)
{
    perspective_manager_instance = this;
    d = new PerspectiveManagerPrivate{this};
}

PerspectiveManager::~PerspectiveManager()
{

}
