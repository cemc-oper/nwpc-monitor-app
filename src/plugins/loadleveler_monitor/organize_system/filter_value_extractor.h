#pragma once

#include "../model/query_category.h"
#include "filter_condition.h"

namespace LoadLevelerMonitor{

namespace Model{
class QueryItem;
}

namespace OrganizeSystem{

class LOADLEVELER_MONITOR_EXPORT QueryCategoryValueExtractor: public FilterValueExtractor
{
public:
    QueryCategoryValueExtractor();
    ~QueryCategoryValueExtractor();

    void setQueryCategory(const Model::QueryCategory &category);

    QVariant extract(QList<Model::QueryItem *> row);

private:
    int findCategoryIndex(QList<Model::QueryItem *> row);

    Model::QueryCategory category_;
};

}

}
