#pragma once

#include "query_category.h"

#include <QVector>
#include <QHash>
#include <QObject>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class LlqCommandManager;
class QueryModel;

class LlqCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlqCommandManagerPrivate(LlqCommandManager *parent = 0);

    void initLlqCategoryList();

    QVector<QueryCategory> categoryList();
    QueryCategory findQueryCategory(const QString result_title);

    QueryCategory findSerialJobDetailQueryCategory(const QString &result_label) const;
    QueryCategory findParellelJobDetailQueryCategory(const QString &result_label) const;

    QueryModel *buildQueryModelFromResponse(const QString &response_str);
    QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_json_document);

signals:

public slots:

private:
    QueryModel *buildDefaultQueryModel(const QString &output);
    QueryModel *buildDetailQueryModel(const QString &output);

    bool isDetailQuery(const QString &command, const QStringList &arguments) const;

    LlqCommandManager *p;

    QVector<QueryCategory> default_query_category_list_;
    QVector<QueryCategory> serial_job_detail_category_list_;
    QHash<QString, QueryCategory> serial_job_detail_category_hash_;
    QVector<QueryCategory> parallel_job_detail_category_list_;
    QHash<QString, QueryCategory> parallel_job_detail_category_hash_;

    friend class LlqCommandManager;
};

}

}
