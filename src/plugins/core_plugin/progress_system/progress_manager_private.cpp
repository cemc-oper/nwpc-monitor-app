#include "progress_manager_private.h"
#include "progress_manager.h"
#include "progress_item_widget.h"
#include "progress_view.h"

#include <QIcon>
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
    status_bar_widget_->deleteLater();
}

void ProgressManagerPrivate::init()
{
    status_bar_widget_ = new ProgressStatusBarWidget;
    status_bar_widget_->hide();
}

void ProgressManagerPrivate::setProgressView(ProgressView *view){
    progress_view_ = view;
}

ProgressView *ProgressManagerPrivate::progressView(){
    return progress_view_;
}

ProgressStatusBarWidget *ProgressManagerPrivate::statusBarWidget()
{
    return status_bar_widget_;
}

ProgressItemWidget *ProgressManagerPrivate::addTask(const QFuture<void> &future, const QString &title)
{
    qDebug()<<"[ProgressManagerPrivate::addTask] add a task:"<<title;
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>{};
    task_list_.append(watcher);
    connect(watcher, &QFutureWatcherBase::progressRangeChanged, this, &ProgressManagerPrivate::updateStatusBarWidget);
    connect(watcher, &QFutureWatcherBase::progressValueChanged, this, &ProgressManagerPrivate::updateStatusBarWidget);
    connect(watcher, &QFutureWatcherBase::finished, this, &ProgressManagerPrivate::updateStatusBarWidget);

    ProgressItemWidget *progress_widget = new ProgressItemWidget;
    progress_widget->setTitle(title);
    connect(watcher, &QFutureWatcherBase::progressValueChanged, progress_widget, &ProgressItemWidget::setProgressValue);
    connect(watcher, &QFutureWatcherBase::finished, progress_widget, &ProgressItemWidget::slotProgressFinish);
    progress_view_->addProgressItemWidget(progress_widget);

    watcher->setFuture(future);

    updateStatusBarWidget();

    qDebug()<<"[ProgressManagerPrivate::addTask] end"<<title;
    return progress_widget;
}

void ProgressManagerPrivate::updateStatusBarWidget()
{
    // visibility
    bool has_running_task = false;
    foreach(QFutureWatcher<void> *future, task_list_)
    {
        if(future->isRunning())
        {
            has_running_task = true;
            break;
        }
    }

    status_bar_widget_->setVisible(has_running_task);

    // value
    const int perTaskRange = 100;
    int value = 0;
    int running_task_count = 0;
    foreach(QFutureWatcher<void> *future, task_list_)
    {
        if(!future->isRunning())
        {
            continue;
        }
        int min = future->progressMinimum();
        int max = future->progressMaximum();
        int range = max - min;
        if(range < 0)
            continue;
        int cur_value = future->progressValue();
        value += perTaskRange * (cur_value - min) / range ;
        running_task_count++;
    }
    status_bar_widget_->setProgressRange(0, perTaskRange * running_task_count);
    status_bar_widget_->slotSetProgressValue(value);
}
