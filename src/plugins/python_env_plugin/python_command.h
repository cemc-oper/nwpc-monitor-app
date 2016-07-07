#pragma once

#include "python_env_global.h"

#include <util/shell_command.h>

namespace PythonEnv{

class PYTHON_ENV_EXPORT PythonCommand : public Util::ShellCommand
{
    Q_OBJECT
public:
    explicit PythonCommand(QObject *parent = 0);

signals:


public slots:

private:


};

}
