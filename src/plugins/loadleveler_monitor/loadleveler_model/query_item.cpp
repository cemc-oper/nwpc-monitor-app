#include "query_item.h"

#include <QDateTime>
#include <QtDebug>

using namespace LoadLevelerMonitor::LoadLevelerModel;

QueryItem::QueryItem():
    QStandardItem{},
    item_type_{ItemType::NormalItem}
{

}

QueryItem::QueryItem(const QString &text):
    QStandardItem{text},
    item_type_{ItemType::NormalItem}
{

}

QueryItem::QueryItem(const QueryItem &other):
    QStandardItem{other},
    item_type_{other.item_type_}
{

}

QueryItem::~QueryItem()
{

}

QVariant QueryItem::data(int role) const
{
    if ( role == Role::SortRole )
    {
        if(item_type_ == ItemType::NumberItem)
            return text().toInt();
        else
            return QStandardItem::data(Qt::DisplayRole);
    }
    return QStandardItem::data(role);
}

QList<QStandardItem *> QueryItem::buildFromQueryRecord(
        const QString &line,
        const QueryCategoryList &category_list)
{
    QList<QStandardItem *> row;
    int pos = 0;
    for(int i = 0; i < category_list.size(); i++)
    {
        QueryCategory c = category_list[i];
        QString item_string = line.mid(pos, c.token_length_);

        QueryItem *item = new QueryItem{};
        item->category_ = c;
        if(c.value_type_ == QueryValueType::String)
        {
            item->setText(item_string.trimmed());
            item->setItemType(QueryItem::ItemType::NormalItem);
        }
        else if(c.value_type_ == QueryValueType::Number)
        {
            item->setText(item_string.trimmed());
            item->setItemType(QueryItem::ItemType::NumberItem);
        }
        else if(c.value_type_ == QueryValueType::Date)
        {
            QDateTime date_time = QDateTime::fromString(item_string.trimmed(), "M/d HH:mm");
            item->setText(date_time.toString("MM/dd HH:mm"));
            item->setItemType(QueryItem::ItemType::DateItem);
        }
        else
        {
            qWarning()<<"[JobQueryItem::buildFromOutputLine] result type not supported:"<<c.value_type_;
            item->setText(item_string.trimmed());
            item->setItemType(ItemType::UnknownItem);
        }
        row<<item;

        pos += c.token_length_ + 1;
    }

    return row;
}

QList<QStandardItem *> QueryItem::buildFromDetailQueryRecord(
        const QStringList &lines,
        const QueryCategoryList &category_list)
{
    QList<QStandardItem *> row;

    //TODO: 使用更高效的方法，当前多次遍历lines，需要改为只遍历一次lines
    QMap<QString, QStandardItem*> id_to_item_map;
    foreach(QString line, lines)
    {
        int index = line.indexOf(": ");
        if (index == -1)
            continue;

        QString label = line.left(index).trimmed();
        if(!category_list.containsLabel(label))
        {
            continue;
        }
        QueryCategory c = category_list.categoryFromLabel(label);

        QString value = line.mid(index + 2).trimmed();
        QueryItem *item = new QueryItem{};
        item->category_ = c;
        if(c.value_type_ == QueryValueType::String)
        {
            item->setText(value);
            item->setItemType(QueryItem::ItemType::NormalItem);
        }
        else if(c.value_type_ == QueryValueType::Number)
        {
            item->setText(value);
            item->setItemType(QueryItem::ItemType::NumberItem);
        }
        else if(c.value_type_ == QueryValueType::Date)
        {
            QDateTime date_time = QDateTime::fromString(value, "M/d HH:mm");
            item->setText(date_time.toString("MM/dd HH:mm"));
            item->setItemType(QueryItem::ItemType::DateItem);
        }
        else if(c.value_type_ == QueryValueType::FullDate)
        {
            // TODO：本地系统为中文，无法使用 ddd MMM 解析英文系统的日期
            //QDateTime date_time = QDateTime::fromString(value, "ddd MMM d hh:mm:ss yyyy"); // Tue Aug 23 01:54:30 2016
            //item->setText(date_time.toString("ddd MMM d hh:mm:ss yyyy"));
            //item->setItemType(JobQueryItem::ItemType::FullDateItem);

            item->setText(value);
            item->setItemType(QueryItem::ItemType::NormalItem);
        }
        else
        {
            qWarning()<<"[JobQueryItem::buildDetailQueryRecord] result type not supported:"<<c.value_type_;
            item->setText(value);
            item->setItemType(ItemType::UnknownItem);
        }
        id_to_item_map[c.id_] = item;
    }

    foreach(QueryCategory c, category_list.categoryList())
    {
        if(id_to_item_map.contains(c.id_))
            row<<id_to_item_map[c.id_];
        else
            row<<new QueryItem{};
    }

    return row;
}

void QueryItem::setItemType(const ItemType &item_type)
{
    item_type_ = item_type;
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
    item_type_ = other.item_type_;
    return *this;
}
