#include "special_record_parser.h"

using namespace LoadLevelerMonitor::Model;

TaskInstanceCountParser::TaskInstanceCountParser():
    QueryRecordParser{}
{

}

TaskInstanceCountParser::TaskInstanceCountParser(const QVariantList &):
    QueryRecordParser{}
{

}

/**
 *  example:
   Master Task
   -----------

      Executable   : /cma/g1/nwp_qu/SMSOUT/rafs/cold/00/model/fcst.job1
      Exec Args    :
      Num Task Inst: 1
      Task Instance: cma08n06:-1:,

   Task
   ----

      Num Task Inst: 512
 */
QString TaskInstanceCountParser::parse(const QStringList &lines)
{
    for(int i=0; i<lines.length()-3; i++)
    {
        if(!lines[i].startsWith("   Task"))
            continue;
        if(!lines[i+1].startsWith("   ----"))
            continue;
        if(!lines[i+3].startsWith("      Num Task Inst: "))
            continue;
        return lines[i+3].mid(QString("      Num Task Inst: ").length()).trimmed();
    }
    return QString();
}
