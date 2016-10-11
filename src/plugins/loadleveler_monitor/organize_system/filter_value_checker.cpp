#include "filter_value_checker.h"

#include <QRegularExpression>
#include <QtDebug>

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
    QString s = value.toString();
    if(operator_type_ == OperatorType::Contain)
    {
        return s.contains(value_);
    }
    else if(operator_type_ == OperatorType::Equal)
    {
        return s == value_;
    }
    else if(operator_type_ == OperatorType::NotContain)
    {
        return !s.contains(value_);
    }
    else if(operator_type_ == OperatorType::StartWith)
    {
        return s.startsWith(value_);
    }
    else if(operator_type_ == OperatorType::EndsWith)
    {
        return s.endsWith(value_);
    }
    else if(operator_type_ == OperatorType::RegExp)
    {
        QRegularExpression re(value_);
        QRegularExpressionMatch match = re.match(s);
        return match.hasMatch();
    }
    else
    {
        qFatal("[StringChecker::isFit] unknown operator type");
        return false;
    }
}

NumberChecker::NumberChecker()
{

}

NumberChecker::~NumberChecker()
{

}

void NumberChecker::setCondition(NumberChecker::OperatorType oper_type, double value)
{
    operator_type_ = oper_type;
    value_ = value;
}

bool NumberChecker::isFit(const QVariant &value)
{
    Q_ASSERT(value.canConvert(QVariant::Double));
    bool ok = false;
    double n = value.toDouble(&ok);

    if(operator_type_ == OperatorType::GreaterThan)
    {
        return n > value_;
    }
    else if(operator_type_ == OperatorType::Equal)
    {
        return n == value_;
    }
    else if(operator_type_ == OperatorType::NotEqual)
    {
        return n != value_;
    }
    else if(operator_type_ == OperatorType::LessThan)
    {
        return n < value_;
    }
    else
    {
        qFatal("[NumberChecker::isFit] unknown operator type");
        return false;
    }
}
