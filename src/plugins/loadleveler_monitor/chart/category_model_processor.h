#pragma once

#include "../model/query_category.h"
#include "../model/query_category_list.h"
#include "model_processor.h"
#include "processor_condition.h"

#include <QObject>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace QtCharts{
class QChart;
}
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPlugin;

namespace Model{
class QueryModel;
}

namespace Chart{


class CategoryProcessorCondition : public ProcessorCondition
{
public:
    CategoryProcessorCondition(const Model::QueryCategoryList &category_list);
    ~CategoryProcessorCondition();

    bool isMatch(Model::QueryModel *query_model);

private:
    Model::QueryCategoryList category_list_;
};


class CategoryModelProcessor : public ModelProcessor
{
    Q_OBJECT
public:
    explicit CategoryModelProcessor(QObject *parent = nullptr);

    void setQueryCategoryList(const Model::QueryCategoryList &category_list);

    QtCharts::QChart *generateChart() = 0;

signals:

public slots:

private slots:

protected:
    Model::QueryCategoryList category_list_;
};


class SingleCategorCountProcessor : public CategoryModelProcessor
{
    Q_OBJECT
public:
    explicit SingleCategorCountProcessor(QObject *parent = nullptr);

    QtCharts::QChart *generateChart();

signals:

public slots:

private slots:

protected:

};

}

}
