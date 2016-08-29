#include "progress_manager_private.h"
#include "progress_manager.h"
#include "progress_item_widget.h"
#include "progress_view.h"

#include <QtDebug>

using namespace Core::ProgressSystem;

ProgressManagerPrivate::ProgressManagerPrivate(ProgressManager *parent) :
    QObject{parent},
    p{parent}
{

}

ProgressManagerPrivate::~ProgressManagerPrivate()
{
    qDeleteAll(task_list_);
    task_list_.clear();
}

ProgressItemWidget *ProgressManagerPrivate::addTask(const QFuture<void> &future, const QString &title)
{
    qDebug()<<"[ProgressManagerPrivate::addTask] add a task:"<<title;
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>{};
    task_list_.append(watcher);
    watcher->setFuture(future);

    ProgressItemWidget *progress_widget = new ProgressItemWidget;
    progress_widget->setTitle(title);

    connect(watcher, &QFutureWatcher<void>::progressValueChanged,
            [=](int progress_value){
        progress_widget->setProgressValue(progress_value);
    });

    connect(watcher, &QFutureWatcher<void>::finished, [=](){
        progress_widget->setProgressValue(progress_widget->getProgressMaxValue());
    });

    progress_view_->addProgressItemWidget(progress_widget);
    return progress_widget;
}
