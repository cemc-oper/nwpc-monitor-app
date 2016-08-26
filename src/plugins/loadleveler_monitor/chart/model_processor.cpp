#include "model_processor.h"
#include "../model/query_model.h"

#include <QtCharts/QChart>

using namespace LoadLevelerMonitor::Chart;
using namespace LoadLevelerMonitor::Model;
using namespace QtCharts;

ModelProcessor::ModelProcessor(QObject *parent) :
    QObject{parent}
{

}

void ModelProcessor::setQueryModel(QueryModel *query_model)
{
    query_model_ = query_model;
}

void ModelProcessor::setDisplayName(const QString &display_name)
{
    display_name_ = display_name;
}

QString ModelProcessor::displayName() const
{
    return display_name_;
}
