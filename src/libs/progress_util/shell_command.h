#pragma once

#include "progress_util_global.h"

#include "synchronous_job.h"

#include <QObject>

namespace ProgressUtil{

struct PROGRESS_UTIL_SHARED_EXPORT CommandStep{
    explicit CommandStep(const QString &program, const QStringList &arguments);
    QString program_;
    QStringList arguments_;
};

class PROGRESS_UTIL_SHARED_EXPORT ShellCommand : public QObject
{
    Q_OBJECT
public:
    explicit ShellCommand(QObject *parent = 0);

    void addCommandStep(const QString& program, const QStringList& argument_list);

    void run();

    ProgressUtil::SynchronousJobResponse runCommandStep(const CommandStep &step);

signals:
    void signalStdOutString(const QString &out);
    void signalStdErrString(const QString &err);
    void signalFinished(int exit_code, QProcess::ExitStatus exitStatus);
    void signalSuccess();

protected:
    QList<CommandStep> command_steps_;
};

}
