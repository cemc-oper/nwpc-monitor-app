#pragma once

#include "shell_command.h"

#include <QRunnable>
#include <QFutureInterface>


QT_BEGIN_NAMESPACE
class QThreadPool;
QT_END_NAMESPACE

namespace ProgressUtil{

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

}
