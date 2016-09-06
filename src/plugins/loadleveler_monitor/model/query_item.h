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
        SortRole = Qt::UserRole + 110
    };

    void setValueType(const QueryValueType &query_value_type);
    void setCategory(const QueryCategory &category);
    QueryCategory category() const;

    QueryItem &operator = (const QueryItem &right);

    QVariant data(int role = Qt::UserRole + 1) const;

    static QList<QStandardItem *> buildDefaultQueryRow(
            const QString &line, const QueryCategoryList &category_list);

    static QList<QStandardItem *> buildDetailQueryRow(
            const QStringList &lines, const QueryCategoryList &category_list);

private:
    static QStandardItem *buildDefaultQueryItem(
            const QueryCategory &category, const QString &line, int begin_pos, int end_pos);
    static QStandardItem *buildDetailQueryItem(const QueryCategory &category, const QStringList &lines);

    static void setQueryItemValue(const QueryCategory &category, const QString &value, QueryItem *query_item);

    QueryValueType query_value_type_;
    QueryCategory category_;
};

}
}
