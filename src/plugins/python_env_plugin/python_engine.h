#pragma once

#include "python_env_global.h"

#include <QObject>
#include <QString>

namespace PythonEnv{

class PythonCommand;

class PYTHON_ENV_EXPORT PythonEngine : public QObject
{
    Q_OBJECT
public:
    explicit PythonEngine(QObject *parent = 0);
    ~PythonEngine();

    QString pythonDistributionDir() const;
    void setPythonDistributionDir(const QString &pythonDistributionDir);

    QString pythonExecutableProgramPath() const;
    void setPythonExecutableProgramPath(const QString &pythonExecutableProgramPath);


    PythonCommand *createPythonCommand();
    void executePythonScript(PythonCommand *command, const QString &script_path, const QStringList &argument_list);

signals:

public slots:

private:
    QString python_distribution_dir_;
    QString python_executable_program_path_;

};

}
