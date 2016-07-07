#pragma once

#include "util_global.h"

namespace Util{

class ShellCommand;

class UTILSHARED_EXPORT ShellCommandUtil
{

public:
    ShellCommandUtil();

    static void runShellCommand(ShellCommand* shell_command);
};

}
