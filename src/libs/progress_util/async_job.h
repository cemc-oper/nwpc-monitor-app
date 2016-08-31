#pragma once

#include <QRunnable>
#include <QFutureInterface>
#include <QFuture>

QT_BEGIN_NAMESPACE
class QThreadPool;
QT_END_NAMESPACE

namespace ProgressUtil{

class ShellCommand;

class AsyncShellCommandJob : public QRunnable
{
public:
    AsyncShellCommandJob(ShellCommand *command);

    ~AsyncShellCommandJob();

    void setPool(QThreadPool *pool);

    void run() override;

    QFuture<void> future();

    static QFuture<void> runJob(ShellCommand *command);

private:
    ShellCommand *command_;
    QFutureInterface<void> future_interface_;
};

template <typename RunObject>
class AsyncRunJob: public QRunnable
{
public:
    AsyncRunJob(RunObject *run_object):
        run_object_{run_object}
    {
        future_interface_.setRunnable(this);
        future_interface_.reportStarted();
        future_interface_.setThreadPool(QThreadPool::globalInstance());
        future_interface_.setProgressRange(0, 100);
    }

    ~AsyncRunJob()
    {
        future_interface_.reportFinished();
    }

    void setPool(QThreadPool *pool)
    {
        future_interface_.setThreadPool(pool);
    }

    void run() override
    {
        run_object_->asyncRun(future_interface_);
    }

    QFuture<void> future()
    {
        return future_interface_.future();
    }

    static QFuture<void> runJob(RunObject *run_object)
    {
        QThreadPool *pool = QThreadPool::globalInstance();
        auto async_job = new AsyncRunJob{run_object};
        QFuture<void> future = async_job->future();
        pool->start(async_job);
        return future;
    }

private:
    RunObject *run_object_;
    QFutureInterface<void> future_interface_;
};

}
