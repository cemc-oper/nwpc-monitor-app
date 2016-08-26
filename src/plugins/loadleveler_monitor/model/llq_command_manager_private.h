#pragma once

#include "query_category.h"
#include "query_category_list.h"

#include <QHash>
#include <QMultiMap>
#include <QSet>
#include <QObject>

namespace LoadLevelerMonitor{

namespace Chart{
class CategoryModelProcessor;
class ProcessorCondition;
class ModelProcessor;
}

namespace Model{

class LlqCommandManager;
class QueryModel;

class LlqCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlqCommandManagerPrivate(LlqCommandManager *parent = 0);
    ~LlqCommandManagerPrivate();

    void initCategoryList();

    QueryCategory findQueryCategory(const QString result_title);
    QueryCategory findSerialJobDetailQueryCategory(const QString &label) const;
    QueryCategory findParellelJobDetailQueryCategory(const QString &label) const;

    QueryModel *buildQueryModelFromResponse(const QString &response_str);
    QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_json_document);

    void initModelProcessor();
    Chart::CategoryModelProcessor *modelDataProcessor();

    QSet<Chart::ModelProcessor*> &processorList(){
        return processor_list_;
    }

    QSet<Chart::ProcessorCondition*> &processorConditionList(){
        return processor_condition_list_;
    }

    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> &processorMap(){
        return processor_map_;
    }

signals:

public slots:

private:
    QueryModel *buildDefaultQueryModel(const QString &output);
    QueryModel *buildDetailQueryModel(const QString &output);

    bool isDetailQuery(const QString &command, const QStringList &arguments) const;

    void registerSingleCategoryCountProcessorMap(const QString &category_id);
    void registerProcessorMap(Chart::ProcessorCondition* condition, Chart::ModelProcessor* processor);

    LlqCommandManager *p;

    QueryCategoryList default_query_category_list_;
    QueryCategoryList serial_job_detail_category_list_;
    QueryCategoryList parallel_job_detail_category_list_;

    Chart::CategoryModelProcessor *model_data_processor_;

    QSet<Chart::ModelProcessor*> processor_list_;
    QSet<Chart::ProcessorCondition*> processor_condition_list_;
    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> processor_map_;

    friend class LlqCommandManager;
};

}

}
