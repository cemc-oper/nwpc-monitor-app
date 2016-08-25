#include "model_category_processor.h"

#include "../model/query_model.h"
#include "../model/query_item.h"

#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QMap>

using namespace LoadLevelerMonitor::Chart;
using namespace LoadLevelerMonitor::Model;
using namespace QtCharts;

/**
 * CategoryProcessorCondition
 */

CategoryProcessorCondition::CategoryProcessorCondition(const QueryCategoryList &category_list):
    ProcessorCondition{},
    category_list_{category_list}
{

}

CategoryProcessorCondition::~CategoryProcessorCondition()
{

}

bool CategoryProcessorCondition::isMatch(QueryModel *query_model)
{
    QueryCategoryList model_category_list = query_model->categoryList();
    for(int i=0; i<category_list_.size();i++)
    {
        if(!model_category_list.containsId(category_list_[i].id_))
            return false;
    }
    return true;
}


/**
 * ModelCategoryProcessor
 */

ModelCategoryProcessor::ModelCategoryProcessor(QObject *parent) :
    ModelProcessor{parent}
{

}

void ModelCategoryProcessor::setQueryCategoryList(const QueryCategoryList &category_list)
{
    category_list_ = category_list;
}

QChart *ModelCategoryProcessor::generateChart()
{
    Q_ASSERT(query_model_);
    Q_ASSERT(category_list_.length() > 0);

    QueryCategory category = category_list_[0];
    Q_ASSERT(query_model_->categoryList().containsId(category.id_));

    QChart *chart = new QChart();

    QBarSet *set = new QBarSet(category.display_name_);

    int col_index = query_model_->categoryList().indexFromId(category.id_);
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
    chart->setTitle(category.display_name_);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(x_axis_titles);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}
