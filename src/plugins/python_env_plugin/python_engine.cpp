#include "python_engine.h"

#include <QProcess>
#include <QtDebug>

using namespace PythonEnv;

PythonEngine::PythonEngine(QObject *parent) :
    QObject(parent),
    process_(new QProcess(this))
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

PythonEngine::~PythonEngine()
{

}

QString PythonEngine::pythonDistributionDir() const
{
    return python_distribution_dir_;
}

void PythonEngine::setPythonDistributionDir(const QString &python_distribution_dir)
{
    python_distribution_dir_ = python_distribution_dir;
}

QString PythonEngine::pythonExecutableProgramPath() const
{
    return python_executable_program_path_;
}

void PythonEngine::setPythonExecutableProgramPath(const QString &python_executable_program_path)
{
    python_executable_program_path_ = python_executable_program_path;
}

bool PythonEngine::executePythonScript(const QString &script_path, const QStringList &argument_list)
{
    qDebug()<<"[PythonEngine::executePythonScript] start";
    if(process_->state() != QProcess::NotRunning)
    {
        qDebug()<<"[PythonEngine::executePythonScript] process not completed.";
        return false;
    }

    QStringList process_arg_list;
    process_arg_list<<script_path;
    foreach(QString str, argument_list)
        process_arg_list<<str;




    process_->start(python_executable_program_path_, process_arg_list);

    qDebug()<<"[PythonEngine::executePythonScript] end";
}
