#pragma once

#include "../model/query_category.h"

#include <QVariant>

namespace LoadLevelerMonitor{

namespace Model{
class QueryItem;
}

namespace OrganizeSystem{

class FilterValueExtractor
{
public:
    FilterValueExtractor();
    virtual ~FilterValueExtractor();

    virtual QVariant extract(QList<Model::QueryItem*> row) = 0;
};


class LOADLEVELER_MONITOR_EXPORT QueryCategoryValueExtractor: public FilterValueExtractor
{
public:
    QueryCategoryValueExtractor();
    ~QueryCategoryValueExtractor();

    void setQueryCategory(const Model::QueryCategory &category);

    QVariant extract(QList<Model::QueryItem *> row);

private:
    Model::QueryCategory category_;
};

}

}
