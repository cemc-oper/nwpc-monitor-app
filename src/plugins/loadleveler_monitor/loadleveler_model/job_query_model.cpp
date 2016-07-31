#include "job_query_model.h"
#include "job_query_item.h"

#include <QJsonArray>

using namespace LoadLevelerMonitor::LoadLevelerModel;

JobQueryModel::JobQueryModel(QObject *parent):
    QStandardItemModel{parent}
{
    setSortRole(JobQueryItem::SortRole);
}

JobQueryModel::~JobQueryModel()
{

}

JobQueryModel *JobQueryModel::buildFromLlqQuery(const QJsonObject &data, QObject *parent)
{
    JobQueryModel *job_query_model = new JobQueryModel(parent);

    QJsonObject command_object = data["command"].toObject();
    QString command = command_object["command"].toString();

    QJsonObject result_object = data["result"].toObject();

    QJsonArray jobs = result_object["jobs"].toArray();

    QJsonObject summary_object = result_object["summary"].toObject();

    int i=1;
    foreach(QJsonValue a_job, jobs)
    {
        QList<QStandardItem*> row = JobQueryItem::buildFromQueryRecord(a_job.toObject());
        JobQueryItem *item = new JobQueryItem(QString::number(i));
        item->setItemType(JobQueryItem::ItemType::NumberItem);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        row.push_front(item);
        job_query_model->invisibleRootItem()->appendRow(row);
        i++;
    }

    job_query_model->setHorizontalHeaderLabels(
        QStringList()
                <<"no"
                <<"id"
                <<"owner"
                <<"submitted time"
                <<"status"
                <<"pri"
                <<"class"
                <<"running on"
    );

    return job_query_model;
}
