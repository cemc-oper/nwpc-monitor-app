#pragma once

#include "query_category.h"
#include "query_category_list.h"

#include <QHash>
#include <QMultiMap>
#include <QSet>
#include <QObject>

namespace LoadLevelerMonitor{

namespace Chart{
class ProcessorCondition;
class ModelProcessor;
}

namespace Model{

class LlclassCommandManager;
class QueryModel;

class LlclassCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlclassCommandManagerPrivate(LlclassCommandManager *parent = 0);
    ~LlclassCommandManagerPrivate();

    void initCategoryList();

    QueryCategory findDefaultQueryCategory(const QString result_title);
    QueryCategory findDetailQueryCategory(const QString &label) const;

    QueryModel *buildQueryModelFromResponse(const QString &response_str);
    QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_json_document);

    void initModelProcessor();

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
    void registerProcessorMap(Chart::ProcessorCondition* condition, Chart::ModelProcessor* processor);

    LlclassCommandManager *p;

    QueryCategoryList default_query_category_list_;
    QueryCategoryList detail_query_category_list_;

    QSet<Chart::ModelProcessor*> processor_list_;
    QSet<Chart::ProcessorCondition*> processor_condition_list_;
    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> processor_map_;

    friend class LlclassCommandManager;
};

}

}
