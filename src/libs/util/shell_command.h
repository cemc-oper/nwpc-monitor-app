#pragma once

#include "util_global.h"

#include <QObject>

QT_BEGIN_NAMESPACE
class QProcess;
QT_END_NAMESPACE

namespace Util{

struct CommandStep{
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

public slots:

protected:
    QList<CommandStep> command_steps_;
    QProcess* process_;
};

}
