#pragma once

#include "llq_category.h"

#include <QStandardItem>
#include <QJsonObject>
#include <QList>
#include <QVector>

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
        UnknownItem = 10,
        NormalItem,
        NumberItem,
        DateTimeItem
    };

    ~JobQueryItem();

    void setItemType(const ItemType &item_type);
    void setCategory(const LlqCategory &category);

    JobQueryItem &operator = (const JobQueryItem &right);

    QVariant data(int role = Qt::UserRole + 1) const;

    static QList<QStandardItem *> buildFromQueryRecord(const QJsonObject &data);
    static QList<QStandardItem *> buildFromOutputLine(const QString &line, const QVector<LlqCategory> &category_list);

private:
    ItemType item_type_;
    LlqCategory category_;
};

}
}
