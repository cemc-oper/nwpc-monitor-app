#include "filter.h"
#include "filter_condition.h"
#include "../model/query_item.h"

#include <QtDebug>

using namespace LoadLevelerMonitor::OrganizeSystem;
using namespace LoadLevelerMonitor::Model;
using namespace std;

Filter::Filter():
    combination_type_{CombinationType::All}
{

}

Filter::~Filter()
{

}

void Filter::setName(const QString &name)
{
    name_ = name;
}

QString Filter::name() const
{
    return name_;
}

void Filter::setCombinationType(const Filter::CombinationType &combination_type)
{
    combination_type_ = combination_type;
}

Filter::CombinationType Filter::combinationType() const
{
    return combination_type_;
}

void Filter::addCondition(shared_ptr<FilterCondition> filter_condition)
{
    condition_list_.append(filter_condition);
}

bool Filter::isFit(QList<QueryItem *> row)
{
    if(combination_type_ == CombinationType::All)
    {
        foreach(shared_ptr<FilterCondition> filter_condition, condition_list_)
        {
            if(!filter_condition->isFit(row))
            {
                return false;
            }
        }
        return true;
    }
    else if(combination_type_ == CombinationType::Any)
    {
        foreach(shared_ptr<FilterCondition> filter_condition, condition_list_)
        {
            if(filter_condition->isFit(row))
            {
                return true;
            }
        }
        return false;

    }else if(combination_type_ == CombinationType::NotAny)
    {
        foreach(shared_ptr<FilterCondition> filter_condition, condition_list_)
        {
            if(filter_condition->isFit(row))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        qCritical()<<"[Filter::isFit] combination type is unknown.";
        return false;
    }
}
