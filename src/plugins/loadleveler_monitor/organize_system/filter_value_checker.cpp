#include "filter_value_checker.h"

using namespace LoadLevelerMonitor::OrganizeSystem;

FilterValueChecker::FilterValueChecker()
{

}

FilterValueChecker::~FilterValueChecker()
{

}

StringChecker::StringChecker():
    FilterValueChecker{}
{

}

StringChecker::~StringChecker()
{

}

void StringChecker::setCondition(StringChecker::OperatorType oper_type, const QString &value)
{
    operator_type_ = oper_type;
    value_ = value;
}

bool StringChecker::isFit(const QVariant &value)
{
    if(operator_type_ == OperatorType::Contain)
    {
        return value.toString().contains(value_);
    }
    else
    {
        return false;
    }
}
