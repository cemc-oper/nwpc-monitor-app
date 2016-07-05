#include "python_engine.h"

using namespace PythonEnv;

PythonEngine::PythonEngine(QObject *parent) : QObject(parent)
{

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

void PythonEngine::executePythonScript(const QString &script_path, const QStringList &argument_list)
{

}
