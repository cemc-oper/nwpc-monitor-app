#pragma once

#include "../loadleveler_model/query_category.h"

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

class ModelDataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit ModelDataProcessor(QObject *parent = nullptr);

    void setQueryModel(Model::QueryModel *query_model);
    void setQueryCategory(const Model::QueryCategory &category);

    QtCharts::QChart *generateChart(QObject *parent = nullptr);

signals:

public slots:

private slots:

private:
    QPointer<Model::QueryModel> query_model_;
    Model::QueryCategory category_;

    friend class LoadLevelerMonitorPlugin;

};

}

}
