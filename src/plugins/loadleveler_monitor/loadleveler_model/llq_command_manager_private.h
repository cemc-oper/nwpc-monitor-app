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

    QVector<QueryCategory> llqCategoryList();
    QueryCategory findLlqQueryCategory(const QString result_title);

    QueryCategory findLlqSerialJobDetailQueryCategory(const QString &result_label) const;
    QueryCategory findLlqParellelJobDetailQueryCategory(const QString &result_label) const;

    QueryModel *buildLlqQueryModelFromResponse(const QString &response_str);
    QueryModel *buildLlqQueryModelFromResponse(const QJsonDocument &response_json_document);

signals:

public slots:

private:
    QueryModel *buildLlqQueryModel(const QString &output);
    QueryModel *buildLlqDetailQueryModel(const QString &output);

    bool isLlqDetailQuery(const QString &command, const QStringList &arguments) const;

    LlqCommandManager *p;

    QVector<QueryCategory> llq_query_category_list_;
    QVector<QueryCategory> llq_serial_job_detail_category_list_;
    QHash<QString, QueryCategory> llq_serial_job_detail_category_hash_;
    QVector<QueryCategory> llq_parallel_job_detail_category_list_;
    QHash<QString, QueryCategory> llq_parallel_job_detail_category_hash_;

    friend class LlqCommandManager;
};

}

}
