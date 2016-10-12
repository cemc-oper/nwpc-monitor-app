#include "filter_condition.h"
#include "filter_value_checker.h"
#include "filter_value_extractor.h"

#include "../model/query_item.h"

using namespace LoadLevelerMonitor::OrganizeSystem;
using namespace LoadLevelerMonitor::Model;


FilterValueChecker::FilterValueChecker()
{

}

FilterValueChecker::~FilterValueChecker()
{

}

FilterValueExtractor::FilterValueExtractor()
{

}

FilterValueExtractor::~FilterValueExtractor()
{

}

FilterCondition::FilterCondition()
{

}

void FilterCondition::setValueChecker(std::shared_ptr<FilterValueChecker> value_checker)
{
    value_checker_ = value_checker;
}

void FilterCondition::setValueExtractor(std::shared_ptr<FilterValueExtractor> value_extractor)
{
    value_extractor_ = value_extractor;
}

bool FilterCondition::isFit(QList<QueryItem *> row)
{
    Q_ASSERT(value_extractor_);
    Q_ASSERT(value_checker_);
    QVariant value = value_extractor_->extract(row);
    return value_checker_->isFit(value);
}

