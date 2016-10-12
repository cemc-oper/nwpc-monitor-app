#pragma once

#include "../loadleveler_monitor_global.h"

#include <QtGlobal>
#include <QVariant>
#include <QList>

#include <memory>

namespace LoadLevelerMonitor{

namespace Model{
class QueryItem;
}

namespace OrganizeSystem{

class FilterValueChecker
{
public:
    FilterValueChecker();
    virtual ~FilterValueChecker();

    virtual bool isFit(const QVariant& value) = 0;
};

class FilterValueExtractor
{
public:
    FilterValueExtractor();
    virtual ~FilterValueExtractor();

    virtual QVariant extract(QList<Model::QueryItem*> row) = 0;
};


class LOADLEVELER_MONITOR_EXPORT FilterCondition
{
public:
    FilterCondition();

    void setValueChecker(std::shared_ptr<FilterValueChecker> value_checker);
    void setValueExtractor(std::shared_ptr<FilterValueExtractor> value_extractor);

    bool isFit(QList<Model::QueryItem *> row);

private:
    std::shared_ptr<FilterValueChecker> value_checker_;
    std::shared_ptr<FilterValueExtractor> value_extractor_;
};

}
}
