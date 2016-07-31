#pragma once

#include <QStandardItem>
#include <QJsonObject>
#include <QList>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class JobQueryItem : public QStandardItem
{
public:
    JobQueryItem();
    JobQueryItem(const QString &text);

    JobQueryItem(const JobQueryItem& other);

    enum ItemType{
        NormalItem,
        NumberItem,
        DateTimeItem
    };

    ~JobQueryItem();

    static QList<QStandardItem *> buildFromQueryRecord(const QJsonObject &data);

    void setItemType(const ItemType &item_type);

    JobQueryItem &operator = (const JobQueryItem &right);
    bool operator < (const JobQueryItem &right) const;

private:
    ItemType item_type_;
};

}
}
