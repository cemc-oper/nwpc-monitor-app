#pragma once

#include "query_item_value_saver.h"

#include <QString>
#include <QVector>

namespace LoadLevelerMonitor{

namespace Model{

struct JobState{
    JobState(const QString &name, const QString abbreviation):
        name_{name}, abbreviation_{abbreviation}
    {}

    QString name_;
    QString abbreviation_;
};

class LOADLEVELER_MONITOR_EXPORT JobStateValueSaver : public QueryItemValueSaver
{
public:
    JobStateValueSaver();
    ~JobStateValueSaver();

    virtual void setItemValue(QueryItem *query_item, const QString &value);
private:
    static const QVector<JobState> job_state_list_;
};


}

}
