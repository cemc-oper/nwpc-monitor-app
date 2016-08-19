#include "shell_command.h"

#include <QProcess>
#include <QtDebug>

using namespace Util;
using namespace ProgressUtil;

CommandStep::CommandStep(const QString &program, const QStringList &arguments):
    program_{program},
    arguments_{arguments}
{

}


ShellCommand::ShellCommand(QObject *parent) :
    QObject(parent)
{

}

void ShellCommand::addCommandStep(const QString &program, const QStringList &argument_list)
{
    CommandStep step{program, argument_list};
    command_steps_.append(step);
}

void ShellCommand::run()
{
    int command_step_size = command_steps_.length();
    for(int i=0;i<command_step_size;i++)
    {
        CommandStep command_step = command_steps_.at(i);
        runCommandStep(command_step);
    }

    this->deleteLater();
}

SynchronousJobResponse ShellCommand::runCommandStep(const CommandStep &step)
{
    SynchronousJobResponse response;

    SynchronousJob job;

    response = job.run(step.program_, step.arguments_);

    qDebug()<<"[ShellCommand::runCommandStep] SynchronousJob success";

    emit signalStdOutString(response.std_out_);
    if(!response.std_err_.isEmpty())
    {
        emit signalStdErrString(response.std_err_);
    }

    emit signalFinished(response.exit_code_, response.exit_status_);

    if(response.exit_code_ == 0 && response.exit_status_ == QProcess::NormalExit)
    {
        emit signalSuccess();
    }
    else
    {
        qDebug()<<"[ShellCommand::runCommandStep] SynchronousJob failed";
    }

    return response;
}
