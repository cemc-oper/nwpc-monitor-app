#pragma once

#include <QPointer>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPlugin;

namespace Model{
class QueryModel;
}

namespace Chart{

class ProcessorCondition
{
public:
    ProcessorCondition();
    virtual ~ProcessorCondition();

    virtual bool isMatch(Model::QueryModel *query_model) = 0;

};

}

}
