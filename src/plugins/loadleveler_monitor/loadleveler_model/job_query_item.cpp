#include "job_query_item.h"

#include <QDateTime>

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

void JobQueryItem::setItemType(const ItemType &item_type)
{
    item_type_ = item_type;
}

JobQueryItem &JobQueryItem::operator =(const JobQueryItem &other)
{
    QStandardItem::operator=(other);
    item_type_ = other.item_type_;
    return *this;
}

bool JobQueryItem::operator <(const JobQueryItem &right) const
{
    if(item_type_ == ItemType::NumberItem)
        return text().toInt() < right.text().toInt();
    else
        return QStandardItem::operator <(right);
}
