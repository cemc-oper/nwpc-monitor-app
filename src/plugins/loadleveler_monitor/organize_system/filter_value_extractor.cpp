#include "filter_value_extractor.h"

#include "../model/query_item.h"

#include <QtDebug>

using namespace LoadLevelerMonitor::OrganizeSystem;
using namespace LoadLevelerMonitor::Model;

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
    int index = findCategoryIndex(row);
    if(index == -1)
    {
        qCritical()<<"[QueryCategoryValueExtractor::extract] category is not in row.";
        return QVariant();
    }

    QueryItem *item = row[index];
    QVariant value = category_.value_saver_->getItemValue(item, QueryItem::ValueRole);

    return value;
}

int QueryCategoryValueExtractor::findCategoryIndex(QList<QueryItem *> row)
{
    int index = -1;
    for(int i = 0; i < row.size(); i++)
    {
        if(row[i]->category() == category_)
        {
            index = i;
            break;
        }
    }
    return index;
}
