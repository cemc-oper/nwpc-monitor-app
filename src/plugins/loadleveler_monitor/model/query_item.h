#pragma once

#include "query_category.h"
#include "query_category_list.h"

#include <QStandardItem>
#include <QJsonObject>
#include <QList>
#include <QVector>

namespace LoadLevelerMonitor{

namespace Model{

class LOADLEVELER_MONITOR_EXPORT QueryItem : public QStandardItem
{
public:
    QueryItem();
    QueryItem(const QString &text);
    QueryItem(const QueryItem& other);
    ~QueryItem();

    enum Role{
        ValueRole = Qt::UserRole + 100,
        SortRole = Qt::UserRole + 110
    };

    void setCategory(const QueryCategory &category);
    QueryCategory category() const;

    QueryItem &operator = (const QueryItem &right);

    QVariant data(int role = Qt::UserRole + 1) const;

    static QList<QStandardItem *> buildDefaultQueryRow(
            const QString &line, const QueryCategoryList &category_list);

    static QList<QStandardItem *> buildDetailQueryRow(
            const QStringList &lines, const QueryCategoryList &category_list);

    static QueryItem *createIndexNoItem(const QueryCategory &num_category, int num);

private:
    static QStandardItem *buildDefaultQueryItem(const QueryCategory &category, const QString &line);
    static QStandardItem *buildDetailQueryItem(const QueryCategory &category, const QStringList &lines);

    QueryCategory category_;
};

}
}
