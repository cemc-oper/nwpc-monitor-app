#include "job_query_item.h"

#include <QDateTime>
#include <QtDebug>

using namespace LoadLevelerMonitor::LoadLevelerModel;

JobQueryItem::JobQueryItem():
    QStandardItem{},
    item_type_{ItemType::NormalItem}
{

}

JobQueryItem::JobQueryItem(const QString &text):
    QStandardItem{text},
    item_type_{ItemType::NormalItem}
{

}

JobQueryItem::JobQueryItem(const JobQueryItem &other):
    QStandardItem{other},
    item_type_{other.item_type_}
{

}

JobQueryItem::~JobQueryItem()
{

}

QVariant JobQueryItem::data(int role) const
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

QList<QStandardItem *> JobQueryItem::buildFromQueryRecord(
        const QString &line,
        const QVector<LlqQueryCategory> &category_list,
        const QHash<QString, LlqQueryCategory> &category_hash)
{
    QList<QStandardItem *> row;
    int pos = 0;
    for(int i = 0; i < category_list.size(); i++)
    {
        LlqQueryCategory c = category_list[i];
        QString item_string = line.mid(pos, c.token_length_);

        JobQueryItem *item = new JobQueryItem{};
        item->category_ = c;
        if(c.value_type_ == LlqQueryCategory::ValueType::String)
        {
            item->setText(item_string.trimmed());
            item->setItemType(JobQueryItem::ItemType::NormalItem);
        }
        else if(c.value_type_ == LlqQueryCategory::ValueType::Number)
        {
            item->setText(item_string.trimmed());
            item->setItemType(JobQueryItem::ItemType::NumberItem);
        }
        else if(c.value_type_ == LlqQueryCategory::ValueType::Date)
        {
            QDateTime date_time = QDateTime::fromString(item_string.trimmed(), "M/d HH:mm");
            item->setText(date_time.toString("MM/dd HH:mm"));
            item->setItemType(JobQueryItem::ItemType::DateItem);
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

QList<QStandardItem *> JobQueryItem::buildFromDetailQueryRecord(
        const QStringList &lines,
        const QVector<LlqQueryCategory> &category_list,
        const QHash<QString, LlqQueryCategory> &category_hash)
{
    QList<QStandardItem *> row;

    //TODO: 使用更高效的方法，当前多次遍历lines，需要改为只遍历一次lines
    foreach(LlqQueryCategory c, category_list)
    {
        foreach(QString line, lines)
        {
            int index = line.indexOf(": ");
            if (index == -1)
                continue;
            QString label = line.left(index).trimmed();
            if(label != c.label_)
            {
                continue;
            }
            QString value = line.mid(index + 2).trimmed();
            JobQueryItem *item = new JobQueryItem{};
            item->category_ = c;
            if(c.value_type_ == LlqQueryCategory::ValueType::String)
            {
                item->setText(value);
                item->setItemType(JobQueryItem::ItemType::NormalItem);
            }
            else if(c.value_type_ == LlqQueryCategory::ValueType::Number)
            {
                item->setText(value);
                item->setItemType(JobQueryItem::ItemType::NumberItem);
            }
            else if(c.value_type_ == LlqQueryCategory::ValueType::Date)
            {
                QDateTime date_time = QDateTime::fromString(value, "M/d HH:mm");
                item->setText(date_time.toString("MM/dd HH:mm"));
                item->setItemType(JobQueryItem::ItemType::DateItem);
            }
            else if(c.value_type_ == LlqQueryCategory::ValueType::FullDate)
            {
                // TODO：本地系统为中文，无法使用 ddd MMM 解析英文系统的日期
                //QDateTime date_time = QDateTime::fromString(value, "ddd MMM d hh:mm:ss yyyy"); // Tue Aug 23 01:54:30 2016
                //item->setText(date_time.toString("ddd MMM d hh:mm:ss yyyy"));
                //item->setItemType(JobQueryItem::ItemType::FullDateItem);

                item->setText(value);
                item->setItemType(JobQueryItem::ItemType::NormalItem);
            }
            else
            {
                qWarning()<<"[JobQueryItem::buildDetailQueryRecord] result type not supported:"<<c.value_type_;
                item->setText(value);
                item->setItemType(ItemType::UnknownItem);
            }
            row<<item;
            break;
        }
    }

    return row;
}

void JobQueryItem::setItemType(const ItemType &item_type)
{
    item_type_ = item_type;
}

void JobQueryItem::setCategory(const LlqQueryCategory &category)
{
    category_ = category;
}

LlqQueryCategory JobQueryItem::category() const
{
    return category_;
}

JobQueryItem &JobQueryItem::operator =(const JobQueryItem &other)
{
    QStandardItem::operator=(other);
    item_type_ = other.item_type_;
    return *this;
}
