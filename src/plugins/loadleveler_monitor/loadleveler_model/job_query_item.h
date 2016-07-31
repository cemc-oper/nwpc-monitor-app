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

    enum Role{
        SortRole = Qt::UserRole + 110
    };

    enum ItemType{
        NormalItem = 11,
        NumberItem,
        DateTimeItem
    };

    ~JobQueryItem();

    QVariant data(int role = Qt::UserRole + 1) const;

    static QList<QStandardItem *> buildFromQueryRecord(const QJsonObject &data);

    void setItemType(const ItemType &item_type);

    JobQueryItem &operator = (const JobQueryItem &right);

private:
    ItemType item_type_;
};

}
}
