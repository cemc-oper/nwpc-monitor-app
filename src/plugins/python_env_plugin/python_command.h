#pragma once

#include "python_env_global.h"

#include <QObject>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
class QProcess;
QT_END_NAMESPACE

namespace PythonEnv{

struct CommandStep{
    explicit CommandStep(const QString &program, const QStringList &arguments);
    QString program_;
    QStringList arguments_;
};

class PYTHON_ENV_EXPORT PythonCommand : public QObject
{
    Q_OBJECT
public:
    explicit PythonCommand(QObject *parent = 0);

    void addCommandStep(const QString& program, const QStringList& argument_list);

    void run();

    void runCommandStep(const CommandStep &step);

signals:


public slots:

private:
    QList<CommandStep> command_steps_;
    QProcess* process_;

};

}
