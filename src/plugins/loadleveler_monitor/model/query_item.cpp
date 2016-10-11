#include "query_item.h"
#include "query_item_value_saver.h"

#include <QDateTime>
#include <QRegularExpression>
#include <QLocale>
#include <QtDebug>

using namespace LoadLevelerMonitor::Model;

QueryItem::QueryItem():
    QStandardItem{}
{

}

QueryItem::QueryItem(const QString &text):
    QStandardItem{text}
{

}

QueryItem::QueryItem(const QueryItem &other):
    QStandardItem{other},
    category_{other.category_}
{

}

QueryItem::~QueryItem()
{

}

QVariant QueryItem::data(int role) const
{
    if ( role == Role::SortRole )
    {
        return category_.value_saver_->getItemValue(this, role);
    }
    return QStandardItem::data(role);
}

QList<QueryItem *> QueryItem::buildDefaultQueryRow(
        const QString &line,
        const QueryCategoryList &category_list)
{
    QList<QueryItem *> row;
    for(int i = 0; i < category_list.size(); i++)
    {
        QueryCategory c = category_list[i];
        QueryItem *item = buildDefaultQueryItem(c, line);
        row<<item;
    }
    return row;
}

QList<QueryItem *> QueryItem::buildDetailQueryRow(
        const QStringList &lines,
        const QueryCategoryList &category_list)
{
    QList<QueryItem *> row;
    //TODO: 使用更高效的方法，当前多次遍历lines，需要改为只遍历一次lines
    foreach(QueryCategory c, category_list.categoryList())
    {
        QueryItem *item = buildDetailQueryItem(c, lines);
        row<<item;
    }
    return row;
}

QueryItem *QueryItem::createIndexNoItem(const QueryCategory &num_category, int num)
{
    QueryItem *item = new QueryItem(QString::number(num));
    item->setCategory(num_category);
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    return item;
}

QueryItem *QueryItem::buildDefaultQueryItem(const QueryCategory &category, const QString &line)
{
    QueryItem *item = new QueryItem{};
    item->setCategory(category);

    // find value: category, line => value
    QString value = category.record_parser_->parse(line);

    // set value
    category.value_saver_->setItemValue(item, value);

    return item;
}

QueryItem *QueryItem::buildDetailQueryItem(const QueryCategory &category, const QStringList &lines)
{
    QueryItem *item = new QueryItem();
    item->setCategory(category);

    // find value: category, lines => value
    QString value = category.record_parser_->parse(lines);

    // set value
    category.value_saver_->setItemValue(item, value);

    return item;
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
    return *this;
}
