#include "shell_command.h"

#include <QProcess>
#include <QtDebug>

using namespace Util;

CommandStep::CommandStep(const QString &program, const QStringList &arguments):
    program_{program},
    arguments_{arguments}
{

}


ShellCommand::ShellCommand(QObject *parent) :
    QObject(parent),
    process_{new QProcess(this)}
{
    connect(process_, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
        [=](int exitCode, QProcess::ExitStatus exitStatus)
        {
            qDebug()<<exitCode;
            qDebug()<<exitStatus;
            qDebug()<<process_->readAllStandardOutput();
        }
    );
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

    //this->deleteLater();
}

void ShellCommand::runCommandStep(const CommandStep &step)
{
    if(process_->state() != QProcess::NotRunning)
    {
        qDebug()<<"[PythonCommand::runCommandStep] process not completed.";
        return;
    }
    process_->start(step.program_, step.arguments_);
}
