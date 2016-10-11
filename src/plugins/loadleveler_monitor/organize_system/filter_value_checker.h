#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QVariant>

namespace LoadLevelerMonitor{

namespace OrganizeSystem{

class FilterValueChecker
{
public:
    FilterValueChecker();
    virtual ~FilterValueChecker();

    virtual bool isFit(const QVariant& value) = 0;
};

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

}

}
