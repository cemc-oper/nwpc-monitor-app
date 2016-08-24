#include "query_model.h"
#include "query_item.h"
#include "llq_command_manager.h"

#include <QJsonArray>
#include <QtDebug>

using namespace LoadLevelerMonitor::LoadLevelerModel;

QueryModel::QueryModel(QObject *parent):
    QStandardItemModel{parent}
{
    query_type_ = QueryType::UnknownQuery;
    setSortRole(QueryItem::SortRole);
}

QueryModel::~QueryModel()
{

}

void QueryModel::setCategoryList(const QueryCategoryList &category_list)
{
    category_list_ = category_list;
}

QueryType QueryModel::queryType() const
{
    return query_type_;
}

void QueryModel::setQueryType(QueryType query_type)
{
    query_type_ = query_type;
}

bool QueryModel::isEmpty() const
{
    return rowCount() == 0;
}

QueryModel *QueryModel::buildFromLlqDefaultQueryResponse(const QStringList &lines, QObject *parent)
{
    // check whether llq query is success.
    if(lines[0].startsWith("llq:"))
    {
        if(lines[0].startsWith("llq: There is currently no job status to report."))
        {
            // TODO: 没有job
            QueryModel *job_model = new QueryModel();
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
    QueryCategoryList category_list;
    for(int i=0;i<category_title_list.size(); i++)
    {
        category_list.append(LlqCommandManager::findDefaultQueryCategory(category_title_list[i]));
        category_list[i].token_length_ = category_column_width[i];
        if(!category_list[i].isValid())
        {
            qDebug()<<"[JobQueryModel::buildFromLlqResponseLines] category is not supported:"<<category_title_list[i];
        }
    }

    QueryCategory row_num_category = LlqCommandManager::findDefaultQueryCategory("No.");

    QueryModel *job_query_model = new QueryModel(parent);
    job_query_model->setQueryType(QueryType::LlqDefaultQuery);


    for(int i=2; i < lines.size() - 3; i++ )
    {
        QList<QStandardItem*> row = QueryItem::buildFromQueryRecord(lines[i], category_list);
        QueryItem *item = new QueryItem(QString::number(i-1));
        item->setItemType(QueryItem::ItemType::NumberItem);
        item->setCategory(row_num_category);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        row.push_front(item);
        job_query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    job_query_model->setCategoryList(category_list);

    // set header titles
    QStringList header_labels;
    foreach(QueryCategory c, category_list.categoryList())
    {
        header_labels.append(c.display_name_);
    }
    job_query_model->setHorizontalHeaderLabels(header_labels);

    return job_query_model;
}

QueryModel *QueryModel::buildFromLlqDetailQueryResponse(const QStringList &lines, QObject *parent)
{
    // check whether llq query is success.
    if(lines[0].startsWith("llq:"))
    {
        if(lines[0].startsWith("llq: There is currently no job status to report."))
        {
            // TODO: 没有job
            QueryModel *job_model = new QueryModel();
            return job_model;
        }
        else
        {
            qDebug()<<"[JobQueryModel::buildFromLlqDetailQueryResponse] failure detected:"<<lines[0];
            return nullptr;
        }
    }

    if( lines.length() < 3 )
    {
        qWarning()<<"[JobQueryModel::buildFromLlqDetailQueryResponse] unsupported output:"<<lines;
        return nullptr;
    }

    QueryModel *job_query_model = new QueryModel(parent);
    job_query_model->setQueryType(QueryType::LlqDetailQuery);

    // last two lines is a summary
    QString summary_line = lines[lines.length()-2];

    QVector<int> record_start_line_no_list;
    for(int i=0; i < lines.length() - 3; i++)
    {
        if(lines[i].startsWith("====="))
            record_start_line_no_list.push_back(i);
    }
    record_start_line_no_list.push_back(lines.length() -2);

    QueryCategoryList category_list;
    QueryCategory row_num_category = LlqCommandManager::findDefaultQueryCategory("No.");

    for(int record_no = 0; record_no < record_start_line_no_list.size() - 1; record_no++)
    {
        int begin_line_no = record_start_line_no_list[record_no];
        int end_line_no = record_start_line_no_list[record_no+1];
        //qDebug()<<record_start_line_no_list[record_no];
        QStringList record_lines = lines.mid(begin_line_no, end_line_no - begin_line_no);

        // find job step type
        QString job_step_type;
        for(int i=0; i<record_lines.length(); i++)
        {
            QString line = record_lines[i].trimmed() ;
            if(line.startsWith("Step Type: "))
            {
                job_step_type = line.mid(11);
                //qDebug()<<job_step_type;
                break;
            }
        }

        if(job_step_type == "Serial")
        {
            category_list = LlqCommandManager::serialJobDetailQueryCategoryList();
        }
        else
        {
            category_list = LlqCommandManager::parellelJobDetailQueryCategoryList();
        }

        QList<QStandardItem*> row = QueryItem::buildFromDetailQueryRecord(record_lines, category_list);
        QueryItem *item = new QueryItem(QString::number(record_no+1));
        item->setItemType(QueryItem::ItemType::NumberItem);
        //item->setCategory(row_num_category);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        row.push_front(item);
        job_query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    job_query_model->setCategoryList(category_list);

    // set header titles
    QStringList header_labels;
    foreach(QueryCategory c, category_list.categoryList())
    {
        header_labels.append(c.display_name_);
    }
    job_query_model->setHorizontalHeaderLabels(header_labels);

    return job_query_model;
}
