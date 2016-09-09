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
    for(int i = 0; i < category_list.size(); i++)
    {
        QueryCategory c = category_list[i];
        QStandardItem *item = buildDefaultQueryItem(c, line);
        row<<item;
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

QStandardItem *QueryItem::buildDefaultQueryItem(const QueryCategory &category, const QString &line)
{
    QueryItem *item = new QueryItem{};
    item->setCategory(category);

    // find value: category, line => value
    QString value = category.record_parser_->parse(line);

    // set value
    category.value_saver_->setItemValue(item, value);

    return item;
}

QStandardItem *QueryItem::buildDetailQueryItem(const QueryCategory &category, const QStringList &lines)
{
    QueryItem *item = new QueryItem();
    item->setCategory(category);

    // find value: category, lines => value
    QString value = category.record_parser_->parse(lines);

    // set value
    category.value_saver_->setItemValue(item, value);

    return item;
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
