#pragma once

#include "../loadleveler_monitor_global.h"

#include <QSortFilterProxyModel>
#include <memory>

namespace LoadLevelerMonitor{

namespace Model{
class QueryModel;
}

namespace OrganizeSystem{

class Filter;

class LOADLEVELER_MONITOR_EXPORT FilterQueryModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FilterQueryModel(QObject *parent = nullptr);

    void setFilter(std::shared_ptr<Filter> filter);

    void setSourceModel(Model::QueryModel *source_model);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    void setSourceModel(QAbstractItemModel *source_model) override;

    std::shared_ptr<Filter> filter_;
};

}

}
