#include "query_util.h"


bool LoadLevelerMonitor::Model::QueryUtil::isDetailQuery(const QString &command, const QStringList &arguments)
{
    Q_UNUSED(arguments);
    if(command.indexOf("-l") == -1)
        return false;
    else
        return true;
}
