#include "percent_bar_processor.h"
#include "../model/query_model.h"

#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtDebug>

using namespace LoadLevelerMonitor::Chart;
using namespace LoadLevelerMonitor::Model;
using namespace QtCharts;

PercentBarProcessorCondition::PercentBarProcessorCondition(QueryCategory item_category,
        QueryCategory total_category,
        QueryCategory free_category)
{
    QueryCategoryList list;
    list.append(item_category);
    list.append(total_category);
    list.append(free_category);
    setCategoryList(list);
}


PercentBarProcessor::PercentBarProcessor(QueryCategory item_category,
        QueryCategory total_category,
        QueryCategory free_category,
        QObject *parent):
    CategoryModelProcessor{parent},
    item_category_{item_category},
    total_category_{total_category},
    free_category_{free_category}
{
    QueryCategoryList list;
    list.append(item_category_);
    list.append(total_category_);
    list.append(free_category_);
    setQueryCategoryList(list);
}

QtCharts::QChart *PercentBarProcessor::generateChart()
{
    Q_ASSERT(query_model_);
    Q_ASSERT(category_list_.length() == 3);

    // TODO: check model condition
//    QueryCategory category = category_list_[0];
//    Q_ASSERT(query_model_->categoryList().containsId(category.id_));

    QChart *chart = new QChart();

    QBarSet *used_set = new QBarSet("used slots");
    QBarSet *free_set = new QBarSet("free slots");
    QStringList x_axis_titles;

    int item_index = query_model_->categoryList().indexFromId(item_category_.id_);
    int total_index = query_model_->categoryList().indexFromId(total_category_.id_);
    int free_index = query_model_->categoryList().indexFromId(free_category_.id_);

    int row_count = query_model_->rowCount();

    QStandardItem *root = query_model_->invisibleRootItem();
    for(int i=0;i<row_count;i++)
    {
        QStandardItem *item = root->child(i, item_index);
        QStandardItem *total_item = root->child(i, total_index);
        QStandardItem *free_item = root->child(i, free_index);

        QString free_text = free_item->text();
        if(free_text.at(free_text.length()-1) == '+')
            free_text = free_text.left(free_text.length()-1);

        bool is_number_ok = false;

        int free_number = free_text.toInt(&is_number_ok);
        if(!is_number_ok)
        {
            qWarning()<<"[PercentBarProcessor::generateChart] free text can't convert to int:" << free_text;
            continue;
        }

        QString total_text = total_item->text();
        if(total_text.at(total_text.length()-1) == '+')
            total_text = total_text.left(total_text.length()-1);

        int total_number = total_text.toInt(&is_number_ok);
        if(!is_number_ok)
        {
            qWarning()<<"[PercentBarProcessor::generateChart] total text can't convert to int:" << total_text;
            continue;
        }

        int used_number = total_number - free_number;
        x_axis_titles<<item->text();
        *used_set<<used_number;
        *free_set<<free_number;
    }

    QPercentBarSeries *series = new QPercentBarSeries();
    series->append(used_set);
    series->append(free_set);

    chart->addSeries(series);
    chart->setTitle(display_name_);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(x_axis_titles);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}
