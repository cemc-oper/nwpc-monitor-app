#include "query_item_value_saver.h"
#include "query_item.h"

#include <QRegularExpression>
#include <QDateTime>
#include <QLocale>

#include <QtDebug>

using namespace LoadLevelerMonitor::Model;

void QueryItemValueSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    qWarning()<<"[QueryItemValueSaver::setItemValue] default saver";
    query_item->setText(value);
    query_item->setValueType(QueryValueType::Unknown);
}

void QueryItemStringSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    query_item->setText(value);
    query_item->setValueType(QueryValueType::String);
}

void QueryItemNumberSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    query_item->setText(value);
    query_item->setValueType(QueryValueType::Number);
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
        qWarning()<<"[QueryItem::buildFromQueryRecord] can't parse Date item:"<<value;
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
        if(month > cur_date.month())
        {
            year -= 1;
        }
        QDateTime date_time{QDate{year,month,day}, QTime{hour,minute}};
        query_item->setText(date_time.toString("MM/dd HH:mm"));
        query_item->setValueType(QueryValueType::Date);
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
    }
    else
    {
        qWarning()<<"[QueryItem::buildFromQueryRecord] can't parse FullDateItem:"<<value;
        query_item->setText(value);
        query_item->setValueType(QueryValueType::String);
    }
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
    case QueryValueType::Unknown:
    default:
        qDebug()<<"[QueryItemValueSaverFactory::make] unknown value type";
        return QSharedPointer<QueryItemValueSaver>{new QueryItemValueSaver};
    }
}
