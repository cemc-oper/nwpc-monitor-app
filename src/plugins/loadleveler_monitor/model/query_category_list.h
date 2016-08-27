#pragma once

#include "query_category.h"

#include <QVector>
#include <QHash>

namespace LoadLevelerMonitor{

namespace Model{

class QueryCategoryList
{
public:
    QueryCategoryList();

    const QVector<QueryCategory> &categoryList() const;

    void clear();
    void append(const QueryCategory &category);
    void insert(int pos, const QueryCategory &category);

    int length() const { return list_.length(); }
    int size() const { return list_.size(); }

    QueryCategory &operator[](int i);
    const QueryCategory &operator[](int i) const;

    int indexFromId(const QString &id) const;
    bool containsId(const QString &id) const;
    const QueryCategory &categoryFromId(const QString &id) const;

    int indexFromLabel(const QString &label) const;
    bool containsLabel(const QString &label) const;
    const QueryCategory &categoryFromLabel(const QString &label) const;

private:
    void registerCategory(int index);

    void rebuildHashMap();

    QVector<QueryCategory> list_;

    QHash<QString, int> id_to_category_map_;
    QHash<QString, int> label_to_category_map_;

    //TODO: agly implement
    QueryCategory valid_category_;

};

}

}
