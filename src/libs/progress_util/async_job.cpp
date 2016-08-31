#include "async_job.h"

#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>

using namespace ProgressUtil;


AsyncShellCommandJob::AsyncShellCommandJob(ShellCommand *command):
    command_{command}
{
    future_interface_.setRunnable(this);
    future_interface_.reportStarted();
    future_interface_.setThreadPool(QThreadPool::globalInstance());
    future_interface_.setProgressRange(0, 100);
}

AsyncShellCommandJob::~AsyncShellCommandJob()
{
    future_interface_.reportFinished();
}


void AsyncShellCommandJob::setPool(QThreadPool *pool)
{
    future_interface_.setThreadPool(pool);
}

void AsyncShellCommandJob::run()
{
    command_->asyncRun(future_interface_);
}

QFuture<void> AsyncShellCommandJob::future()
{
    return future_interface_.future();
}

QFuture<void> AsyncShellCommandJob::runJob(ShellCommand *command)
{
    QThreadPool *pool = QThreadPool::globalInstance();
    auto async_job = new AsyncShellCommandJob{command};
    QFuture<void> future = async_job->future();
    pool->start(async_job);
    return future;
}
