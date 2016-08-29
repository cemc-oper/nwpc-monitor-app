#include "progress_manager.h"
#include "progress_manager_private.h"
#include "progress_item_widget.h"
#include "progress_view.h"

using namespace Core::ProgressSystem;

static ProgressManager *progress_manager_instance = nullptr;
static ProgressManagerPrivate *d = nullptr;

ProgressManager *ProgressManager::instance()
{
    return progress_manager_instance;
}

ProgressView *ProgressManager::progressView()
{
    return d->progressView();
}

void ProgressManager::setProgressView(ProgressView *view)
{
    return d->setProgressView(view);
}

ProgressItemWidget *ProgressManager::addTask(const QFuture<void> &future, const QString &title)
{
    return d->addTask(future, title);
}

ProgressManager::ProgressManager(QObject *parent) :
    QObject{parent}
{
    progress_manager_instance = this;
    d = new ProgressManagerPrivate{this};
}

ProgressManager::~ProgressManager()
{

}
