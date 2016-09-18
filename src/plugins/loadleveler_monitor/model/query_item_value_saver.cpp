#include "query_item_value_saver.h"
#include "special_value_saver.h"
#include "query_item.h"

#include <QRegularExpression>
#include <QLocale>

#include <QtDebug>

using namespace LoadLevelerMonitor::Model;

namespace LoadLevelerMonitor{

namespace Model{

LOADLEVELER_MONITOR_EXPORT QDebug operator <<(QDebug debug, const QueryValueType &value_type)
{
    switch(value_type)
    {
    case QueryValueType::Unknown:
        debug<<"Unknown";
        break;
    case QueryValueType::String:
        debug<<"String";
        break;
    case QueryValueType::Number:
        debug<<"Number";
        break;
    case QueryValueType::Date:
        debug<<"Date";
        break;
    case QueryValueType::FullDate:
        debug<<"FullDate";
        break;
    case QueryValueType::JobState:
        debug<<"JobState";
        break;
    default:
        Q_ASSERT(0);
        debug<<"unspported";
    }

    return debug;
}

}

}

void QueryItemValueSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    qWarning()<<"[QueryItemValueSaver::setItemValue] default saver";
    query_item->setText(value);
    query_item->setValueType(QueryValueType::Unknown);
}

QVariant QueryItemValueSaver::getItemValue(QueryItem *query_item, int role) const
{
    return query_item->data(role);
}

QSharedPointer<QueryItemValueSaver> QueryItemValueSaverFactory::make(QueryValueType value_type)
{
    switch(value_type)
    {
    case QueryValueType::String:
        return QSharedPointer<QueryItemValueSaver>{new QueryItemStringSaver};
        break;
    case QueryValueType::Number:
        return QSharedPointer<QueryItemValueSaver>{new QueryItemNumberSaver};
        break;
    case QueryValueType::Date:
        return QSharedPointer<QueryItemValueSaver>{new QueryItemDateSaver};
        break;
    case QueryValueType::FullDate:
        return QSharedPointer<QueryItemValueSaver>{new QueryItemFullDateSaver};
        break;
    case QueryValueType::JobState:
        return QSharedPointer<QueryItemValueSaver>{new JobStateValueSaver};
        break;
    case QueryValueType::Unknown:
        qDebug()<<"[QueryItemValueSaverFactory::make] unknown value type";
        return QSharedPointer<QueryItemValueSaver>{new QueryItemValueSaver};
    default:
        throw std::invalid_argument(QString("error query value type").toStdString());
    }
}


void QueryItemStringSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    query_item->setText(value);
    query_item->setValueType(QueryValueType::String);
    text_ = value;
}

void QueryItemNumberSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    query_item->setText(value);
    query_item->setValueType(QueryValueType::Number);
    num_ = value.toFloat();
}

QVariant QueryItemNumberSaver::getItemValue(QueryItem *query_item, int role) const
{
    if(role == QueryItem::SortRole)
    {
        return num_;
    }
    else
    {
        return QueryItemValueSaver::getItemValue(query_item, role);
    }
}

void QueryItemDateSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    // Different data has different spaces between date and time, such as:
    //  9/1  08:17  --  2 spaces
    //  8/20 02:52  --  1 space
    // As QDateTime::fromString does not support regular expression,
    // we should use QRegularExpression to get elements of datetime.
    QRegularExpression re("^([0-9]{1,2})/([0-9]{1,2}) {1,2}([0-9][0-9]):([0-9][0-9])");
    QRegularExpressionMatch match = re.match(value);
    if(!match.hasMatch())
    {
        qWarning()<<"[QueryItemDateSaver::setItemValue] can't parse Date item:"<<value;
        query_item->setText(value);
        query_item->setValueType(QueryValueType::String);
    }
    else
    {
        int month = match.captured(1).toInt();
        int day = match.captured(2).toInt();
        int hour = match.captured(3).toInt();
        int minute = match.captured(4).toInt();

        QDate cur_date = QDate::currentDate();
        int year = cur_date.year();
        qDebug()<<month<<cur_date.month();
        if(month > cur_date.month())
        {
            year -= 1;
        }
        QDateTime date_time{QDate{year,month,day}, QTime{hour,minute}};
        query_item->setText(date_time.toString("MM/dd HH:mm"));
        query_item->setValueType(QueryValueType::Date);
        date_time_ = date_time;
    }
}

QVariant QueryItemDateSaver::getItemValue(QueryItem *query_item, int role) const
{
    if(role == QueryItem::SortRole)
    {
        return date_time_;
    }
    else
    {
        return QueryItemValueSaver::getItemValue(query_item, role);
    }
}

void QueryItemFullDateSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    // 本地系统为中文，使用 Qlocale 解析英文系统的日期
    QLocale locale(QLocale::C);
    // Month and day has a spacing of 1 or 2 spaces.
    //  Tue Aug 23 01:54:30 2016
    //  Thu Sep  1 08:55:23 2016
    QDateTime date_time = locale.toDateTime(value, "ddd MMM d hh:mm:ss yyyy");
    if(!date_time.isValid())
        date_time = locale.toDateTime(value, "ddd MMM  d hh:mm:ss yyyy");

    if(date_time.isValid())
    {
        query_item->setText(date_time.toString("MM/dd HH:mm"));
        query_item->setValueType(QueryValueType::FullDate);
        date_time_ = date_time;
    }
    else
    {
        qWarning()<<"[QueryItemFullDateSaver::setItemValue] can't parse FullDateItem:"<<value;
        query_item->setText(value);
        query_item->setValueType(QueryValueType::String);
    }
}

QVariant QueryItemFullDateSaver::getItemValue(QueryItem *query_item, int role) const
{
    if(role == QueryItem::SortRole)
    {
        return date_time_;
    }
    else
    {
        return QueryItemValueSaver::getItemValue(query_item, role);
    }
}


