#include "perspective_manager_private.h"

#include "perspective_manager.h"
#include "iperspective.h"

using namespace Core::PerspectiveSystem;

PerspectiveManagerPrivate::PerspectiveManagerPrivate(PerspectiveManager *parent) :
    QObject(parent),
    q{parent}
{

}

PerspectiveManagerPrivate::~PerspectiveManagerPrivate()
{

}

QVector<IPerspective *> PerspectiveManagerPrivate::perspectiveList()
{
    return perspective_list_;
}

void PerspectiveManagerPrivate::addPerspective(IPerspective *persp)
{
    perspective_list_.append(persp);
}
