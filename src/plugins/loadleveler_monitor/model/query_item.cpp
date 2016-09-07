#include "query_item.h"

#include <QDateTime>
#include <QRegularExpression>
#include <QLocale>
#include <QtDebug>

using namespace LoadLevelerMonitor::Model;

QueryItem::QueryItem():
    QStandardItem{},
    query_value_type_{QueryValueType::String}
{

}

QueryItem::QueryItem(const QString &text):
    QStandardItem{text},
    query_value_type_{QueryValueType::String}
{

}

QueryItem::QueryItem(const QueryItem &other):
    QStandardItem{other},
    query_value_type_{other.query_value_type_}
{

}

QueryItem::~QueryItem()
{

}

QVariant QueryItem::data(int role) const
{
    if ( role == Role::SortRole )
    {
        if(query_value_type_ == QueryValueType::Number)
            return text().toFloat();
        else
            return QStandardItem::data(Qt::DisplayRole);
    }
    return QStandardItem::data(role);
}

QList<QStandardItem *> QueryItem::buildDefaultQueryRow(
        const QString &line,
        const QueryCategoryList &category_list)
{
    QList<QStandardItem *> row;
    int pos = 0;
    for(int i = 0; i < category_list.size(); i++)
    {
        QueryCategory c = category_list[i];
        QStandardItem *item = buildDefaultQueryItem(c, line, pos, pos + c.token_length_);
        row<<item;
        pos += c.token_length_ + 1;
    }
    return row;
}

QList<QStandardItem *> QueryItem::buildDetailQueryRow(
        const QStringList &lines,
        const QueryCategoryList &category_list)
{
    QList<QStandardItem *> row;
    //TODO: 使用更高效的方法，当前多次遍历lines，需要改为只遍历一次lines
    foreach(QueryCategory c, category_list.categoryList())
    {
        QStandardItem *item = buildDetailQueryItem(c, lines);
        row<<item;
    }
    return row;
}

QueryItem *QueryItem::createIndexNoItem(const QueryCategory &num_category, int num)
{
    QueryItem *item = new QueryItem(QString::number(num));
    item->setValueType(QueryValueType::Number);
    item->setCategory(num_category);
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    return item;
}

QStandardItem *QueryItem::buildDefaultQueryItem(
        const QueryCategory &category, const QString &line, int begin_pos, int end_pos)
{
    // find value: category, line, begin_pos, end_pos => value
    QString item_string = line.mid(begin_pos, end_pos-begin_pos);
    QString value = item_string.trimmed();

    // set value
    QueryItem *item = new QueryItem{};
    setQueryItemValue(category, value, item);

    return item;
}

QStandardItem *QueryItem::buildDetailQueryItem(const QueryCategory &category, const QStringList &lines)
{
    QueryItem *item = new QueryItem();

    // find value from lines: category, lines => value
    foreach(QString line, lines)
    {
        int index = line.indexOf(": ");
        if (index == -1)
            continue;

        QString label = line.left(index).trimmed();
        if(label != category.label_)
            continue;

        // value got
        QString value = line.mid(index + 2).trimmed();

        // set value
        setQueryItemValue(category, value, item);
        break;
    }
    return item;
}

/*
 *           QueryCategory
 *   value ================>  QueryItem
 *            value_type_
 */
void QueryItem::setQueryItemValue(const QueryCategory &category, const QString &value, QueryItem *query_item)
{
    query_item->category_ = category;

    if(category.value_type_ == QueryValueType::String)
    {
        query_item->setText(value);
        query_item->setValueType(QueryValueType::String);
    }
    else if(category.value_type_ == QueryValueType::Number)
    {
        query_item->setText(value);
        query_item->setValueType(QueryValueType::Number);
    }
    else if(category.value_type_ == QueryValueType::Date)
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
    else if(category.value_type_ == QueryValueType::FullDate)
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
    else
    {
        qWarning()<<"[JobQueryItem::buildDetailQueryRecord] result type not supported:"<<category.value_type_;
        query_item->setText(value);
        query_item->setValueType(QueryValueType::Unknown);
    }
}

void QueryItem::setValueType(const QueryValueType &query_value_type)
{
    query_value_type_ = query_value_type;
}

void QueryItem::setCategory(const QueryCategory &category)
{
    category_ = category;
}

QueryCategory QueryItem::category() const
{
    return category_;
}

QueryItem &QueryItem::operator =(const QueryItem &other)
{
    QStandardItem::operator=(other);
    query_value_type_ = other.query_value_type_;
    return *this;
}
