#pragma once

#include "llq_category.h"

#include <QVector>
#include <QHash>
#include <QObject>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class LlqCommandManager;
class JobQueryModel;

class LlqCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlqCommandManagerPrivate(LlqCommandManager *parent = 0);

    void initLlqCategoryList();

    QVector<LlqQueryCategory> llqCategoryList();
    LlqQueryCategory findLlqQueryCategory(const QString result_title);

    LlqDetailQueryCategory findLlqSerialJobDetailQueryCategory(const QString &result_label) const;
    LlqDetailQueryCategory findLlqParellelJobDetailQueryCategory(const QString &result_label) const;

    JobQueryModel *buildLlqQueryModelFromResponse(const QString &response_str);
    JobQueryModel *buildLlqQueryModelFromResponse(const QJsonDocument &response_json_document);

signals:

public slots:

private:
    JobQueryModel *buildLlqQueryModel(const QString &output);
    JobQueryModel *buildLlqDetailQueryModel(const QString &output);

    bool isLlqDetailQuery(const QString &command, const QStringList &arguments) const;

    LlqCommandManager *p;

    QVector<LlqQueryCategory> llq_query_category_list_;
    QVector<LlqDetailQueryCategory> llq_serial_job_detail_category_list_;
    QHash<QString, LlqDetailQueryCategory> llq_serial_job_detail_category_hash_;
    QVector<LlqDetailQueryCategory> llq_parallel_job_detail_category_list_;
    QHash<QString, LlqDetailQueryCategory> llq_parallel_job_detail_category_hash_;

    friend class LlqCommandManager;
};

}

}
