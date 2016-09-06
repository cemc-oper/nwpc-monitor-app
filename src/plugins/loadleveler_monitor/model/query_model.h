#pragma once

#include "../loadleveler_monitor_global.h"
#include "query_category.h"
#include "query_category_list.h"

#include <QStandardItemModel>
#include <QJsonObject>
#include <QVector>

namespace LoadLevelerMonitor{

namespace Model{

class LOADLEVELER_MONITOR_EXPORT QueryModel : public QStandardItemModel
{
    Q_OBJECT
public:
    QueryModel(QObject *parent=0);
    ~QueryModel();

    void setCategoryList(const QueryCategoryList &category_list);
    const QueryCategoryList &categoryList() const;

    QueryType queryType() const;
    void setQueryType(QueryType query_type);

    bool isEmpty() const;

    static QueryModel *buildFromLlqDefaultQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);
    static QueryModel *buildFromLlqDetailQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);

    static QueryModel *buildFromLlclassDefaultQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);
    static QueryModel *buildFromLlclassDetailQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);

signals:

public slots:

private:
    static void setHeader(QueryModel *query_model, const QueryCategoryList &category_list);

    QueryCategoryList category_list_;
    QueryType query_type_;
};

}
}
