#include "query_model.h"
#include "query_item.h"
#include "llq_command_manager.h"
#include "llclass_command_manager.h"

#include <QJsonArray>
#include <QtDebug>

using namespace LoadLevelerMonitor::Model;

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

const QueryCategoryList &QueryModel::categoryList() const
{
    return category_list_;
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

    // get category width
    QString category_mark_line = lines[1].trimmed();
    QVector<int> category_column_width = getCategoryColumnWidth(category_mark_line);

    // get category title
    QString category_title_line = lines[0];
    QVector<QString> category_title_list(category_column_width.size());
    int pos = 0;
    std::transform(category_column_width.begin(), category_column_width.end(),
                   category_title_list.begin(), [&pos, &category_title_line](int width){
        QString title = category_title_line.mid(pos, width);
        pos += width + 1;
        return title.trimmed();
    });

    // get category list
    //      use title to find category, and use width to set up parser.
    /*
     *  将提取category数据所需要的信息（token_length_）保存到 category 中，
     *  实际上相当于将创建一个文本解析器，在建立每个 cell 时，使用该解析器从文本中提取信息。
     *  TODO: 创建 Parser 类，负责从文本中 (string/string list) 提取数据，生成 QueryItem。
     *  每个 QueryCateogry 绑定一个 Parser。
     *  每次创建 QueryModel，需要根据输出文本调整 Parser 的参数，匹配该次输出。
     */
    QueryCategoryList category_list;
    pos = 0;
    for(int i=0;i<category_title_list.size(); i++)
    {
        category_list.append(LlqCommandManager::findDefaultQueryCategory(category_title_list[i]));

        if(!category_list[i].isValid())
        {
            qDebug()<<"[JobQueryModel::buildFromLlqResponseLines] category is not supported:"<<category_title_list[i];
        }

        if(QueryTableRecordParser *table_parser = dynamic_cast<QueryTableRecordParser*>(category_list[i].record_parser_.data()))
        {
            table_parser->setArguments(QVariantList() << pos << pos + category_column_width[i]);
        }

        pos += category_column_width[i] + 1;
    }
    QueryCategory row_num_category = LlqCommandManager::findDefaultQueryCategory("No.");

    // get data line range
    int begin_record_line = 2;
    int end_record_line = lines.size() - 3;

    // build model
    QueryModel *query_model = new QueryModel(parent);
    query_model->setQueryType(QueryType::LlqDefaultQuery);
    for(int i = begin_record_line; i < end_record_line; i++ )
    {
        QList<QStandardItem*> row = QueryItem::buildDefaultQueryRow(lines[i], category_list);

        QueryItem *item = QueryItem::createIndexNoItem(row_num_category, i-1);
        row.push_front(item);

        query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    query_model->setCategoryList(category_list);

    // set header titles
    setHeader(query_model, category_list);

    return query_model;
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
    // last two lines is a summary
    QString summary_line = lines[lines.length()-2];

    // get record start line no.
    QVector<int> record_start_line_no_list;
    for(int i=0; i < lines.length() - 3; i++)
    {
        if(lines[i].startsWith("====="))
            record_start_line_no_list.push_back(i);
    }
    record_start_line_no_list.push_back(lines.length() -2);

    // build model
    QueryModel *query_model = new QueryModel(parent);
    query_model->setQueryType(QueryType::LlqDetailQuery);

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

        QList<QStandardItem*> row = QueryItem::buildDetailQueryRow(record_lines, category_list);
        QueryItem *item = QueryItem::createIndexNoItem(row_num_category, record_no+1);
        row.push_front(item);

        query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    query_model->setCategoryList(category_list);

    // set header titles
    setHeader(query_model, category_list);

    return query_model;
}

QueryModel *QueryModel::buildFromLlclassDefaultQueryResponse(const QStringList &lines, QObject *parent)
{
    // check whether llclass query is success.
    if(lines[0].startsWith("llclass:"))
    {
        qDebug()<<"[QueryModel::buildFromLlclassDefaultQueryResponse] failure detected:"<<lines[0];
        return nullptr;
    }

    if( lines.length() < 3 )
    {
        qWarning()<<"[QueryModel::buildFromLlclassDefaultQueryResponse] unsupported output:"<<lines;
        return nullptr;
    }

    // get categories' title
    QStringList category_title_line = lines.mid(0,2);

    QString category_mark_line = lines[2].trimmed();
    QVector<int> category_column_width = getCategoryColumnWidth(category_mark_line);

    QVector<QString> category_title_list(category_column_width.size());
    int pos = 0;
    std::transform(category_column_width.begin(), category_column_width.end(),
                   category_title_list.begin(), [&pos, &category_title_line](int width){
        QString title = category_title_line[0].mid(pos, width).trimmed() +
                category_title_line[1].mid(pos, width).trimmed();
        pos += width + 1;
        return title.trimmed();
    });

    // get category list
    QueryCategoryList category_list;
    pos = 0;
    for(int i=0;i<category_title_list.size(); i++)
    {
        category_list.append(LlclassCommandManager::findDefaultQueryCategory(category_title_list[i]));
        if(!category_list[i].isValid())
        {
            qDebug()<<"[QueryModel::buildFromLlclassDefaultQueryResponse] category is not supported:"
                    <<category_title_list[i];
        }
        if(QueryTableRecordParser *table_parser = dynamic_cast<QueryTableRecordParser*>(category_list[i].record_parser_.data()))
        {
            table_parser->setArguments(QVariantList() << pos << pos + category_column_width[i]);
        }
        pos += category_column_width[i] + 1;

    }

    // get record begin and end line
    int record_line_begin = 3;
    int record_line_end = lines.length() - 1;
    // 检查是否有说明行，例如：
    // Name                 MaxJobCPU     MaxProcCPU  Free   Max Description
    // d+hh:mm:ss     d+hh:mm:ss Slots Slots
    // --------------- -------------- -------------- ----- ----- ---------------------
    // serial_op            undefined      undefined   119   128
    // serial_op1           undefined      undefined   128   128
    // normal               undefined      undefined   179  3328
    // largemem             undefined      undefined   692  1952
    // serial               undefined      undefined   172   192
    // special2             undefined      undefined  1443  3200
    // operation1           undefined      undefined  5267 9999+
    // normal1              undefined      undefined  5267 9999+
    // minijob              undefined      undefined    32  2560
    // operation            undefined      undefined    32  2560
    // --------------------------------------------------------------------------------
    // "Free Slots" values of the classes "normal", "largemem", "special2", "operation1", "normal1", "minijob", "operation" are constrained by the MAX_STARTERS limit(s).
    if(lines.length() > 2 &&
       lines[lines.length() - 3].startsWith(
                "--------------------------------------------------------------------------------"
       )
    )
    {
        record_line_end = lines.length() - 3;
    }

    // build model
    QueryCategory row_num_category = LlclassCommandManager::findDefaultQueryCategory("No.");

    QueryModel *query_model = new QueryModel(parent);
    query_model->setQueryType(QueryType::LlclassDefaultQuery);

    for(int i=record_line_begin; i < record_line_end; i++ )
    {
        QList<QStandardItem*> row = QueryItem::buildDefaultQueryRow(lines[i], category_list);

        QueryItem *item = QueryItem::createIndexNoItem(row_num_category, i-2);
        row.push_front(item);

        query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    query_model->setCategoryList(category_list);

    // set header titles
    setHeader(query_model, category_list);

    return query_model;
}

QueryModel *QueryModel::buildFromLlclassDetailQueryResponse(const QStringList &lines, QObject *parent)
{
    // check whether llclass query is success.
    if(lines[0].startsWith("llclass:"))
    {
        qDebug()<<"[QueryModel::buildFromLlclassDetailQueryResponse] failure detected:"<<lines[0];
        return nullptr;
    }

    if( lines.length() < 3 )
    {
        qWarning()<<"[QueryModel::buildFromLlclassDetailQueryResponse] unsupported output:"<<lines;
        return nullptr;
    }

    // get record begin and end line
    int record_line_begin = 0;
    int record_line_end = lines.length() - 1;
    if(lines.length() > 2 &&
       lines[lines.length() - 3].startsWith(
                "--------------------------------------------------------------------------------"
       )
    )
    {
        record_line_end = lines.length() - 3;
    }

    // record_start_line begin and end
    QVector<int> record_start_line_no_list;
    for(int i=0; i < lines.length(); i++)
    {
        if(lines[i].startsWith("====="))
            record_start_line_no_list.push_back(i);
    }
    record_start_line_no_list.push_back(record_line_end);

    // build model
    QueryModel *query_model = new QueryModel(parent);
    query_model->setQueryType(QueryType::LlqDetailQuery);

    QueryCategoryList category_list = LlclassCommandManager::detailQueryCategoryList();
    QueryCategory row_num_category = LlclassCommandManager::findDefaultQueryCategory("No.");

    for(int record_no = 0; record_no < record_start_line_no_list.size() - 1; record_no++)
    {
        int begin_line_no = record_start_line_no_list[record_no];
        int end_line_no = record_start_line_no_list[record_no+1];
        QStringList record_lines = lines.mid(begin_line_no, end_line_no - begin_line_no);

        QList<QStandardItem*> row = QueryItem::buildDetailQueryRow(record_lines, category_list);

        QueryItem *item = QueryItem::createIndexNoItem(row_num_category, record_no+1);
        row.push_front(item);

        query_model->invisibleRootItem()->appendRow(row);
    }

    // insert no category
    category_list.insert(0, row_num_category);
    query_model->setCategoryList(category_list);

    // set header titles
    setHeader(query_model, category_list);

    return query_model;
}

void QueryModel::setHeader(QueryModel *query_model, const QueryCategoryList &category_list)
{
    QStringList header_labels;
    foreach(QueryCategory c, category_list.categoryList())
    {
        header_labels.append(c.display_name_);
    }
    query_model->setHorizontalHeaderLabels(header_labels);
}
