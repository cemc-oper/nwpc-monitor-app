#include "llq_command_manager_private.h"

#include "llq_command_manager.h"
#include "query_item.h"
#include "query_model.h"

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>

#include <algorithm>

using namespace LoadLevelerMonitor::LoadLevelerModel;

LlqCommandManagerPrivate::LlqCommandManagerPrivate(LlqCommandManager *parent) :
    QObject{parent},
    p{parent}
{

}

void LlqCommandManagerPrivate::initLlqCategoryList()
{
    llq_default_query_category_list_.clear();
    foreach(QStringList record, kLlqDefaultQueryCategoryList)
    {
        llq_default_query_category_list_.append(QueryCategory::createFromStringList(record));
    }

    llq_serial_job_detail_category_list_.clear();
    foreach(QStringList record, kLlqDetailQuerySerialJobCategoryList)
    {
        QueryCategory c = QueryCategory::createFromStringList(record);
        llq_serial_job_detail_category_list_.append(c);
        llq_serial_job_detail_category_hash_[c.label_] = c;
    }

    llq_parallel_job_detail_category_list_.clear();
    foreach(QStringList record, kLlqDetailQueryParallelCategoryList)
    {
        QueryCategory c = QueryCategory::createFromStringList(record);
        llq_parallel_job_detail_category_list_.append(c);
        llq_parallel_job_detail_category_hash_[c.label_] = c;
    }
}

QVector<QueryCategory> LlqCommandManagerPrivate::llqCategoryList()
{
    return llq_default_query_category_list_;
}

QueryCategory LlqCommandManagerPrivate::findLlqQueryCategory(const QString result_title)
{
    QueryCategory result_category;
    for(int i=0; i<llq_default_query_category_list_.length(); i++)
    {
        QueryCategory category = llq_default_query_category_list_[i];
        if( category.label_ == result_title )
        {
            result_category = category;
            break;
        }
    }
    return result_category;
}

QueryCategory LlqCommandManagerPrivate::findLlqSerialJobDetailQueryCategory(const QString &result_label) const
{
    if(llq_serial_job_detail_category_hash_.contains(result_label))
        return llq_serial_job_detail_category_hash_[result_label];
    else
        return QueryCategory();
}

QueryCategory LlqCommandManagerPrivate::findLlqParellelJobDetailQueryCategory(const QString &result_label) const
{
    if(llq_parallel_job_detail_category_hash_.contains(result_label))
        return llq_parallel_job_detail_category_hash_[result_label];
    else
        return QueryCategory();
}

QueryModel *LlqCommandManagerPrivate::buildLlqQueryModelFromResponse(const QString &response_str)
{
    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] begin";

    QJsonDocument doc = QJsonDocument::fromJson(response_str.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] result is not a json string.";
        return nullptr;
    }

    return buildLlqQueryModelFromResponse(doc);
}

QueryModel *LlqCommandManagerPrivate::buildLlqQueryModelFromResponse(const QJsonDocument &response_json_document)
{
    QJsonObject result_object = response_json_document.object();

    if( result_object.contains("error"))
    {
        QString error_message = result_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] ERROR:"<<error_message;
        return nullptr;
    }

    QString app = result_object["app"].toString();
    QString type = result_object["type"].toString();
    QJsonObject data = result_object["data"].toObject();

    QJsonObject request = data["request"].toObject();
    QString command = request["command"].toString();
    QJsonArray arguments = request["arguments"].toArray();
    QStringList arg_list;
    foreach(QJsonValue an_argument, arguments)
    {
        arg_list.append(an_argument.toString());
    }

    QJsonObject message = data["response"].toObject()["message"].toObject();
    QString output_message = message["output"].toString();

    QueryModel *model = nullptr;
    if(isLlqDetailQuery(command, arg_list))
    {
        model = buildLlqDetailQueryModel(output_message);
    }
    else
    {
        model = buildLlqQueryModel(output_message);
    }

    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] end";
    return model;
}

QueryModel *LlqCommandManagerPrivate::buildLlqQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    // 不能直接对每行使用trimmed，因为第一项和最后一项都可能为空，trimmed将破坏数据。
//    std::transform(lines.begin(), lines.end(),
//                   lines.begin(), [=](QString str){
//        return str.trimmed();
//    });

    return QueryModel::buildFromLlqDefaultQueryResponse(lines);
}

QueryModel *LlqCommandManagerPrivate::buildLlqDetailQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    return QueryModel::buildFromLlqDetailQueryResponse(lines);
}

bool LlqCommandManagerPrivate::isLlqDetailQuery(const QString &command, const QStringList &arguments) const
{
    Q_UNUSED(arguments);
    if(command.indexOf("-l") == -1)
        return false;
    else
        return true;
}
