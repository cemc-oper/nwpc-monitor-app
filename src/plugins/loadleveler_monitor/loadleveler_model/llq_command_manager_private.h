#pragma once

#include "query_category.h"
#include "query_category_list.h"

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

    QueryCategory findQueryCategory(const QString result_title);
    QueryCategory findSerialJobDetailQueryCategory(const QString &label) const;
    QueryCategory findParellelJobDetailQueryCategory(const QString &label) const;

    QueryModel *buildQueryModelFromResponse(const QString &response_str);
    QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_json_document);

signals:

public slots:

private:
    QueryModel *buildDefaultQueryModel(const QString &output);
    QueryModel *buildDetailQueryModel(const QString &output);

    bool isDetailQuery(const QString &command, const QStringList &arguments) const;

    LlqCommandManager *p;

    QueryCategoryList default_query_category_list_;
    QueryCategoryList serial_job_detail_category_list_;
    QueryCategoryList parallel_job_detail_category_list_;

    friend class LlqCommandManager;
};

}

}
