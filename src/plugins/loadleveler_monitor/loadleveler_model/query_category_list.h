#pragma once

#include "query_category.h"

#include <QVector>
#include <QHash>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class QueryCategoryList
{
public:
    QueryCategoryList();

    void append(const QueryCategory &category);
    void insert(int pos, const QueryCategory &category);

    int indexFromId(const QString &id) const;
    int indexFromLabel(const QString &label) const;

private:
    void registerCategory(int index);

    void rebuildHashMap();

    QVector<QueryCategory> list_;

    QHash<QString, int> id_to_category_map_;
    QHash<QString, int> label_to_category_map_;

};

}

}
