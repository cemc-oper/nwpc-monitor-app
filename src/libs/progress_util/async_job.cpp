#include "async_job.h"

#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>

using namespace ProgressUtil;


AsyncJob::AsyncJob(ShellCommand *command):
    command_{command}
{
    future_interface_.setRunnable(this);
    future_interface_.reportStarted();
    future_interface_.setThreadPool(QThreadPool::globalInstance());
}


void AsyncJob::setPool(QThreadPool *pool)
{
    future_interface_.setThreadPool(pool);
}

void AsyncJob::run()
{
    command_->asyncRun(future_interface_);
}

QFuture<void> AsyncJob::future()
{
    return future_interface_.future();
}

QFuture<void> AsyncJob::runJob(ShellCommand *command)
{
    QThreadPool *pool = QThreadPool::globalInstance();
    auto async_job = new AsyncJob{command};
    QFuture<void> future = async_job->future();
    pool->start(async_job);
    return future;
}
