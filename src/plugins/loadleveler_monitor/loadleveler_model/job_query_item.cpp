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

QList<QStandardItem *> JobQueryItem::buildFromQueryRecord(const QJsonObject &data)
{
    QList<QStandardItem *> row;
    QString id = data["id"].toString();
    QString owner = data["owner"].toString();

    QString submitted_date = data["submitted"].toObject()["date"].toString();
    QString submitted_time = data["submitted"].toObject()["time"].toString();
    QString submitted_string = submitted_date + " " + submitted_time;
    QDateTime submitted = QDateTime::fromString(submitted_string, "M/d HH:mm");

    QString st = data["st"].toString();
    QString pri = data["pri"].toString();
    QString class_name = data["class"].toString();
    QString running_on = data["running_on"].toString();

    JobQueryItem *id_item = new JobQueryItem(id);
    id_item->setItemType(JobQueryItem::ItemType::NumberItem);
    row<<id_item;
    row<<new JobQueryItem(owner);
    row<<new JobQueryItem(submitted.toString("MM/dd HH:mm"));
    row<<new JobQueryItem(st);
    JobQueryItem *pri_item = new JobQueryItem(pri);
    pri_item->setItemType(JobQueryItem::ItemType::NumberItem);
    row<<pri_item;
    row<<new JobQueryItem(class_name);
    row<<new JobQueryItem(running_on);

    return row;
}

QList<QStandardItem *> JobQueryItem::buildFromOutputLine(const QString &line, const QVector<LlqCategory> &category_list)
{
    QList<QStandardItem *> row;
    int pos = 0;
    for(int i = 0; i < category_list.size(); i++)
    {
        LlqCategory c = category_list[i];
        QString item_string = line.mid(pos, c.token_length_);

        JobQueryItem *item = new JobQueryItem{};
        item->category_ = c;
        if(c.result_type_ == TYPE_STRING)
        {
            item->setText(item_string.trimmed());
            item->setItemType(JobQueryItem::ItemType::NormalItem);
        }
        else if(c.result_type_ == TYPE_NUMBER)
        {
            item->setText(item_string.trimmed());
            item->setItemType(JobQueryItem::ItemType::NumberItem);
        }
        else if(c.result_type_ == TYPE_DATE)
        {
            QDateTime date_time = QDateTime::fromString(item_string.trimmed(), "M/d HH:mm");
            item->setText(date_time.toString("MM/dd HH:mm"));
            item->setItemType(JobQueryItem::ItemType::DateTimeItem);
        }
        else
        {
            qWarning()<<"[JobQueryItem::buildFromOutputLine] result type not supported:"<<c.result_type_;
            item->setText(item_string.trimmed());
            item->setItemType(ItemType::UnknownItem);
        }
        row<<item;

        pos += c.token_length_ + 1;
    }

    return row;
}

void JobQueryItem::setItemType(const ItemType &item_type)
{
    item_type_ = item_type;
}

void JobQueryItem::setCategory(const LlqCategory &category)
{
    category_ = category;
}

LlqCategory JobQueryItem::category() const
{
    return category_;
}

JobQueryItem &JobQueryItem::operator =(const JobQueryItem &other)
{
    QStandardItem::operator=(other);
    item_type_ = other.item_type_;
    return *this;
}
