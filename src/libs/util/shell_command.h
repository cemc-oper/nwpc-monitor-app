#pragma once

#include "util_global.h"

#include <QObject>
#include <QProcess>

namespace Util{

struct UTILSHARED_EXPORT CommandStep{
    explicit CommandStep(const QString &program, const QStringList &arguments);
    QString program_;
    QStringList arguments_;
};

class UTILSHARED_EXPORT ShellCommand : public QObject
{
    Q_OBJECT
public:
    explicit ShellCommand(QObject *parent = 0);

    void addCommandStep(const QString& program, const QStringList& argument_list);

    void run();

    void runCommandStep(const CommandStep &step);

signals:
    void signalStdOutString(const QString &out);
    void signalStdErrString(const QString &err);
    void signalFinished(int exit_code, QProcess::ExitStatus exitStatus);
    void signalSuccess();

private slots:
    void slotProcessFinished(int exit_code, QProcess::ExitStatus exit_status);

protected:
    QList<CommandStep> command_steps_;
    QProcess* process_;
};

}
