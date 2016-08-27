#pragma once

#include "category_model_processor.h"

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPlugin;

namespace Model{
class QueryModel;
}

namespace Chart{

class PercentBarProcessorCondition : public CategoryProcessorCondition
{
public:
    PercentBarProcessorCondition(
            Model::QueryCategory item_category,
            Model::QueryCategory total_category,
            Model::QueryCategory free_category);
    ~PercentBarProcessorCondition(){}
};

class PercentBarProcessor : public CategoryModelProcessor
{
    Q_OBJECT
public:
    explicit PercentBarProcessor(
            Model::QueryCategory item_category,
            Model::QueryCategory total_category,
            Model::QueryCategory free_category,
            QObject *parent = 0);

    QtCharts::QChart *generateChart();

signals:

public slots:

private:
    Model::QueryCategory item_category_;

    Model::QueryCategory total_category_;
    Model::QueryCategory free_category_;
};

}

}
