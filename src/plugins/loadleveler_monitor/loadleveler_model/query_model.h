#pragma once

#include "query_category.h"

#include <QStandardItemModel>
#include <QJsonObject>
#include <QVector>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class QueryModel : public QStandardItemModel
{
    Q_OBJECT
public:
    QueryModel(QObject *parent=0);
    ~QueryModel();

    void setCategoryList(const QVector<QueryCategory> &category_list);

    QueryType queryType() const;
    void setQueryType(QueryType query_type);

    bool isEmpty() const;

    static QueryModel *buildFromLlqDefaultQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);
    static QueryModel *buildFromLlqDetailQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);

signals:

public slots:

private:
    QVector<QueryCategory> category_list_;
    QueryType query_type_;
};

}
}
