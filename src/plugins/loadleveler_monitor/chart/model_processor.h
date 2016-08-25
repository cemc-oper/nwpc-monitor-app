#pragma once

#include "../model/query_category.h"

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

class ModelProcessor : public QObject
{
    Q_OBJECT
public:
    explicit ModelProcessor(QObject *parent = nullptr);

    void setQueryModel(Model::QueryModel *query_model);

    virtual QtCharts::QChart *generateChart() = 0;

signals:

public slots:

private slots:

protected:
    QPointer<Model::QueryModel> query_model_;

    friend class LoadLevelerMonitorPlugin;
};

}

}
