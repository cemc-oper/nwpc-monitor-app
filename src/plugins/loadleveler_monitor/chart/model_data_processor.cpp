#include "model_data_processor.h"

#include "../loadleveler_model/query_model.h"
#include "../loadleveler_model/query_item.h"

#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QMap>

using namespace LoadLevelerMonitor::Chart;
using namespace LoadLevelerMonitor::Model;
using namespace QtCharts;

ModelDataProcessor::ModelDataProcessor(QObject *parent) :
    QObject{parent}
{

}

void ModelDataProcessor::setQueryModel(QueryModel *query_model)
{
    query_model_ = query_model;
}

void ModelDataProcessor::setQueryCategory(const QueryCategory &category)
{
    category_ = category;
}

QChart *ModelDataProcessor::generateChart(QObject *parent)
{
    Q_ASSERT(query_model_);
    Q_ASSERT(category_.isValid());
    Q_ASSERT(query_model_->categoryList().containsId(category_.id_));

    QChart *chart = new QChart();

    QBarSet *set = new QBarSet(category_.display_name_);

    int col_index = query_model_->categoryList().indexFromId(category_.id_);
    int row_count = query_model_->rowCount();

    QMap<QString, int> map;

    QStandardItem *root = query_model_->invisibleRootItem();
    for(int i=0;i<row_count;i++)
    {
        QStandardItem *item = root->child(i, col_index);
        map[item->text()]++;
    }

    QStringList x_axis_titles;

    QMapIterator<QString, int> i(map);
    while (i.hasNext()) {
          i.next();
          x_axis_titles<<i.key();
          *set<<i.value();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    chart->addSeries(series);
    chart->setTitle(category_.display_name_);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(x_axis_titles);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}
