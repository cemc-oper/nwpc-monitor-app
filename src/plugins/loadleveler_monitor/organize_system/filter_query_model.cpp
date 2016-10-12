#include "filter_query_model.h"
#include "filter.h"
#include "../model/query_model.h"
#include "../model/query_item.h"

#include <QtDebug>

#include <exception>

using namespace LoadLevelerMonitor::OrganizeSystem;
using namespace LoadLevelerMonitor::Model;

FilterQueryModel::FilterQueryModel(QObject *parent):
    QSortFilterProxyModel{parent}
{

}

void FilterQueryModel::setFilter(std::shared_ptr<Filter> filter)
{
    filter_ = filter;
}

void FilterQueryModel::setSourceModel(QAbstractItemModel *source_model)
{
    throw std::invalid_argument("[FilterQueryModel::setSourceModel] source model must be QueryModel");
    QSortFilterProxyModel::setSourceModel(source_model);
}

void FilterQueryModel::setSourceModel(LoadLevelerMonitor::Model::QueryModel *source_model)
{
    QSortFilterProxyModel::setSourceModel(source_model);
}

bool FilterQueryModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QAbstractItemModel *model = sourceModel();
    QueryModel *query_model = qobject_cast<QueryModel*>(model);

    Q_ASSERT(query_model);

    if(source_parent != query_model->invisibleRootItem()->index())
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);

    QList<QueryItem*> row;
    for(int i=0;i<query_model->columnCount(source_parent);i++)
    {
        QueryItem* query_item = dynamic_cast<QueryItem*>(query_model->item(source_row, i));
        Q_ASSERT(query_item);
        row.append(query_item);
    }

    return filter_->isFit(row);
}
