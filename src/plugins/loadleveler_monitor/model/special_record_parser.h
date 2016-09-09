#pragma once

#include "query_record_parser.h"

namespace LoadLevelerMonitor{

namespace Model{

class LOADLEVELER_MONITOR_EXPORT TaskInstanceCountParser : public QueryRecordParser
{
public:
    TaskInstanceCountParser();
    TaskInstanceCountParser(const QVariantList &args);

    QString parse(const QStringList &lines) override;
};

}

}
