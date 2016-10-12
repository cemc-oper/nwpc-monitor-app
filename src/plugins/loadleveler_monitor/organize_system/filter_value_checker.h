#pragma once

#include "../loadleveler_monitor_global.h"
#include "filter_condition.h"

#include <QString>
#include <QDateTime>

namespace LoadLevelerMonitor{

namespace OrganizeSystem{

class LOADLEVELER_MONITOR_EXPORT StringChecker: public FilterValueChecker {
public:
    enum class OperatorType{
        Contain,
        Equal,
        StartWith,
        EndsWith,
        NotContain,
        RegExp
    };

    StringChecker();
    ~StringChecker();

    void setCondition(OperatorType oper_type, const QString &value);

    bool isFit(const QVariant& value);

private:
    OperatorType operator_type_;
    QString value_;

};

class LOADLEVELER_MONITOR_EXPORT NumberChecker: public FilterValueChecker {
public:
    enum class OperatorType{
        GreaterThan,
        Equal,
        NotEqual,
        LessThan
    };

    NumberChecker();
    ~NumberChecker();

    void setCondition(OperatorType oper_type, double value);

    bool isFit(const QVariant &value);

private:
    OperatorType operator_type_;
    double value_;
};

class LOADLEVELER_MONITOR_EXPORT DateTimeChecker: public FilterValueChecker {
public:
    enum class OperatorType{
        Before,
        Equal,
        NotEqual,
        After
    };

    DateTimeChecker();
    ~DateTimeChecker();

    void setCondition(OperatorType oper_type, const QDateTime &date_time);

    bool isFit(const QVariant &value);

private:
    OperatorType operator_type_;
    QDateTime value_;
};

class LOADLEVELER_MONITOR_EXPORT BooleanChecker: public FilterValueChecker {
public:
    enum class OperatorType{
        Set,
        Unset
    };

    BooleanChecker();
    ~BooleanChecker();

    void setCondition(OperatorType oper_type);

    bool isFit(const QVariant &value);

private:
    OperatorType operator_type_;
};

}

}
