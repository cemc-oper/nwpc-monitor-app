#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QDateTime>
#include <QSharedPointer>

namespace LoadLevelerMonitor{

namespace Model{

class QueryItem;

enum class QueryValueType{
    Unknown,
    String,
    Number,
    Date,       // 'MM/DD HH:MM'
    FullDate,    // Mon Aug 22 02:25:09 2016

    // special value
    JobState    // job status: Running/R, Idle/I
};

LOADLEVELER_MONITOR_EXPORT QDebug operator <<(QDebug debug, const QueryValueType &value_type);


class LOADLEVELER_MONITOR_EXPORT QueryItemValueSaver
{
public:
    QueryItemValueSaver(){}
    virtual ~QueryItemValueSaver(){}

    virtual void setItemValue(QueryItem *query_item, const QString &value);
    virtual QVariant getItemValue(QueryItem *query_item, int role = Qt::DisplayRole) const;
};

class LOADLEVELER_MONITOR_EXPORT QueryItemValueSaverFactory
{
public:
    static QSharedPointer<QueryItemValueSaver>  make(QueryValueType value_type);
};

// value savers

class LOADLEVELER_MONITOR_EXPORT QueryItemStringSaver: public QueryItemValueSaver
{
public:
    QueryItemStringSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
protected:
    QString text_;
};


class LOADLEVELER_MONITOR_EXPORT QueryItemNumberSaver: public QueryItemValueSaver
{
public:
    QueryItemNumberSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
    virtual QVariant getItemValue(QueryItem *query_item, int role = Qt::DisplayRole) const override;

protected:
    float num_;
};

class LOADLEVELER_MONITOR_EXPORT QueryItemDateSaver: public QueryItemValueSaver
{
public:
    QueryItemDateSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
    virtual QVariant getItemValue(QueryItem *query_item, int role = Qt::DisplayRole) const override;

protected:
    QDateTime date_time_;
};

class LOADLEVELER_MONITOR_EXPORT QueryItemFullDateSaver: public QueryItemValueSaver
{
public:
    QueryItemFullDateSaver(): QueryItemValueSaver{}{}

    void setItemValue(QueryItem *query_item, const QString &value) override;
    virtual QVariant getItemValue(QueryItem *query_item, int role = Qt::DisplayRole) const override;

protected:
    QDateTime date_time_;
};

}

}
