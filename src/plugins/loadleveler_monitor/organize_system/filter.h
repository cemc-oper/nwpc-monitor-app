#pragma once

#include "../loadleveler_monitor_global.h"
#include <QtGlobal>
#include <QList>
#include <QString>
#include <memory>

namespace LoadLevelerMonitor{

namespace Model{
class QueryItem;
}

namespace OrganizeSystem{

class FilterCondition;

class LOADLEVELER_MONITOR_EXPORT Filter
{
public:
    enum CombinationType{
        All,
        Any,
        NotAny
    };

    Filter();
    virtual ~Filter();

    void setName(const QString &name);
    QString name() const;

    void setCombinationType(const CombinationType &combination_type);
    CombinationType combinationType() const;

    void addCondition(std::shared_ptr<FilterCondition> filter_condition);

    bool isFit(QList<Model::QueryItem *> row);


private:
    QString name_;
    CombinationType combination_type_;

    QList<std::shared_ptr<FilterCondition>> condition_list_;
};

}

}
