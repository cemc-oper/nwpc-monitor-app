#include "job_query_model.h"
#include "job_query_item.h"
#include "llq_command_manager.h"

#include <QJsonArray>
#include <QtDebug>

using namespace LoadLevelerMonitor::LoadLevelerModel;

JobQueryModel::JobQueryModel(QObject *parent):
    QStandardItemModel{parent}
{
    setSortRole(JobQueryItem::SortRole);
}

JobQueryModel::~JobQueryModel()
{

}

void JobQueryModel::setCategoryList(const QVector<LlqCategory> &category_list)
{
    category_list_ = category_list;
}

JobQueryModel *JobQueryModel::buildFromLlqQuery(const QJsonObject &data, QObject *parent)
{
    JobQueryModel *job_query_model = new JobQueryModel(parent);

    QJsonObject command_object = data["command"].toObject();
    QString command = command_object["command"].toString();

    QJsonObject response_object = data["response"].toObject();

    QJsonArray jobs = response_object["jobs"].toArray();

    QJsonObject summary_object = response_object["summary"].toObject();

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

JobQueryModel *JobQueryModel::buildFromLlqResponseLines(const QStringList &lines, QObject *parent)
{
    // check whether llq query is success.
    if(lines[0].startsWith("llq:"))
    {
        if(lines[0].startsWith("llq: There is currently no job status to report."))
        {
            // TODO: 没有job
            JobQueryModel *job_model = new JobQueryModel();
            return job_model;
        }
        else
        {
            qDebug()<<"[JobQueryModel::buildFromLlqResponseLines] failure detected:"<<lines[0];
            return nullptr;
        }
    }

    if( lines.length() < 2 )
    {
        qWarning()<<"[JobQueryModel::buildFromLlqResponseLines] unsupported output:"<<lines;
        return nullptr;
    }

    // get categories' title
    QString category_title_line = lines[0];
    QString category_mark_line = lines[1].trimmed();

    QStringList category_marks = category_mark_line.split(' ');

    QVector<int> category_column_width(category_marks.size());

    std::transform(category_marks.begin(), category_marks.end(),
                   category_column_width.begin(), [=](QString str){
        return str.length();
    });

    QVector<QString> category_title_list(category_column_width.size());
    int pos = 0;

    std::transform(category_column_width.begin(), category_column_width.end(),
                   category_title_list.begin(), [&pos, &category_title_line](int width){
        QString title = category_title_line.mid(pos, width);
        pos += width + 1;
        return title.trimmed();
    });

    // get category list
    QVector<LlqCategory> category_list(category_title_list.size());
    for(int i=0;i<category_title_list.size(); i++)
    {
        category_list[i] = LlqCommandManager::findCategory(category_title_list[i]);
        category_list[i].token_length_ = category_column_width[i];
        if(!category_list[i].isValid())
        {
            qDebug()<<"[JobQueryModel::buildFromLlqResponseLines] category is not supported:"<<category_title_list[i];
        }
    }

    LlqCategory row_num_category = LlqCommandManager::findCategory("No.");

    JobQueryModel *job_query_model = new JobQueryModel(parent);
    for(int i=2; i < lines.size() - 3; i++ )
    {
        QList<QStandardItem*> row = JobQueryItem::buildFromOutputLine(lines[i], category_list);
        JobQueryItem *item = new JobQueryItem(QString::number(i-1));
        item->setItemType(JobQueryItem::ItemType::NumberItem);
        item->setCategory(row_num_category);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        row.push_front(item);
        job_query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    // set header titles
    QStringList header_labels;
    foreach(LlqCategory c, category_list)
    {
        header_labels.append(c.display_name_);
    }
    job_query_model->setHorizontalHeaderLabels(header_labels);

    return job_query_model;
}
