#pragma once

#include "../loadleveler_monitor_global.h"

#include <QtGlobal>
#include <memory>

namespace LoadLevelerMonitor{

namespace Model{
class QueryItem;
}

namespace OrganizeSystem{

class FilterValueChecker;
class FilterValueExtractor;

class LOADLEVELER_MONITOR_EXPORT FilterCondition
{
public:
    FilterCondition();

    void setValueChecker(std::shared_ptr<FilterValueChecker> value_checker);
    void setValueExtractor(std::shared_ptr<FilterValueExtractor> value_extractor);

    bool isFit(QList<Model::QueryItem *> row);

private:
    std::shared_ptr<FilterValueChecker> value_checker_;
    std::shared_ptr<FilterValueExtractor> value_extractor_;
};

}
}
