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
