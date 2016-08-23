#pragma once

#include "query_category.h"

#include <QStandardItem>
#include <QJsonObject>
#include <QList>
#include <QVector>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class QueryItem : public QStandardItem
{
public:
    QueryItem();
    QueryItem(const QString &text);

    QueryItem(const QueryItem& other);

    enum Role{
        SortRole = Qt::UserRole + 110
    };

    enum ItemType{
        UnknownItem = 10,
        NormalItem,
        NumberItem,
        DateItem,
        FullDateItem
    };

    ~QueryItem();

    void setItemType(const ItemType &item_type);
    void setCategory(const QueryCategory &category);
    QueryCategory category() const;

    QueryItem &operator = (const QueryItem &right);

    QVariant data(int role = Qt::UserRole + 1) const;

    static QList<QStandardItem *> buildFromQueryRecord(
            const QString &line,
            const QVector<QueryCategory> &category_list,
            const QHash<QString, QueryCategory> &category_hash = QHash<QString, QueryCategory>());

    static QList<QStandardItem *> buildFromDetailQueryRecord(
            const QStringList &lines,
            const QVector<QueryCategory> &category_list,
            const QHash<QString, QueryCategory> &category_hash = QHash<QString, QueryCategory>());

private:
    ItemType item_type_;
    QueryCategory category_;
};

}
}
