#include "filter_value_extractor.h"

#include "../model/query_item.h"

using namespace LoadLevelerMonitor::OrganizeSystem;
using namespace LoadLevelerMonitor::Model;

FilterValueExtractor::FilterValueExtractor()
{

}

FilterValueExtractor::~FilterValueExtractor()
{

}

QueryCategoryValueExtractor::QueryCategoryValueExtractor()
{

}

QueryCategoryValueExtractor::~QueryCategoryValueExtractor()
{

}

void QueryCategoryValueExtractor::setQueryCategory(const QueryCategory &category)
{
    category_ = category;
}

QVariant QueryCategoryValueExtractor::extract(QList<QueryItem *> row)
{
    return QVariant();
}
