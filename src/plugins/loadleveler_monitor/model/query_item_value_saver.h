#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>

namespace LoadLevelerMonitor{

namespace Model{

class QueryItem;

class LOADLEVELER_MONITOR_EXPORT QueryItemValueSaver
{
public:
    QueryItemValueSaver(){}
    virtual ~QueryItemValueSaver(){}

    virtual void setItemValue(QueryItem *query_item, const QString &value);
};


class LOADLEVELER_MONITOR_EXPORT QueryItemStringSaver: public QueryItemValueSaver
{
public:
    QueryItemStringSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
};


class LOADLEVELER_MONITOR_EXPORT QueryItemNumberSaver: public QueryItemValueSaver
{
public:
    QueryItemNumberSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
};

class LOADLEVELER_MONITOR_EXPORT QueryItemDateSaver: public QueryItemValueSaver
{
public:
    QueryItemDateSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
};

class LOADLEVELER_MONITOR_EXPORT QueryItemFullDateSaver: public QueryItemValueSaver
{
public:
    QueryItemFullDateSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
};

}

}
