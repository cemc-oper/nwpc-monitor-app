#include "llq_command_manager_private.h"

#include "llq_command_manager.h"
#include "job_query_item.h"
#include "job_query_model.h"

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
    llq_query_category_list_.clear();
    foreach(QStringList record, LLQ_QUERY_CATEGARY_LIST)
    {
        llq_query_category_list_.append(LlqQueryCategory::createFromStringList(record));
    }

    llq_serial_job_detail_category_list_.clear();
    foreach(QStringList record, kLlqDetailQuerySerialJobCategoryList)
    {
        LlqDetailQueryCategory c = LlqDetailQueryCategory::createFromStringList(record);
        llq_serial_job_detail_category_list_.append(c);
        llq_serial_job_detail_category_hash_[c.result_label_] = c;
    }

    llq_parallel_job_detail_category_list_.clear();
    foreach(QStringList record, kLlqDetailQueryParallelCategoryList)
    {
        LlqDetailQueryCategory c = LlqDetailQueryCategory::createFromStringList(record);
        llq_parallel_job_detail_category_list_.append(c);
        llq_parallel_job_detail_category_hash_[c.result_label_] = c;
    }
}

QVector<LlqQueryCategory> LlqCommandManagerPrivate::llqCategoryList()
{
    return llq_query_category_list_;
}

LlqQueryCategory LlqCommandManagerPrivate::findLlqQueryCategory(const QString result_title)
{
    LlqQueryCategory result_category;
    for(int i=0; i<llq_query_category_list_.length(); i++)
    {
        LlqQueryCategory category = llq_query_category_list_[i];
        if( category.result_title_ == result_title )
        {
            result_category = category;
            break;
        }
    }
    return result_category;
}

LlqDetailQueryCategory LlqCommandManagerPrivate::findLlqSerialJobDetailQueryCategory(const QString &result_label) const
{
    if(llq_serial_job_detail_category_hash_.contains(result_label))
        return llq_serial_job_detail_category_hash_[result_label];
    else
        return LlqDetailQueryCategory();
}

LlqDetailQueryCategory LlqCommandManagerPrivate::findLlqParellelJobDetailQueryCategory(const QString &result_label) const
{
    if(llq_parallel_job_detail_category_hash_.contains(result_label))
        return llq_parallel_job_detail_category_hash_[result_label];
    else
        return LlqDetailQueryCategory();
}

JobQueryModel *LlqCommandManagerPrivate::buildLlqQueryModelFromResponse(const QString &response_str)
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

JobQueryModel *LlqCommandManagerPrivate::buildLlqQueryModelFromResponse(const QJsonDocument &response_json_document)
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

    JobQueryModel *model = nullptr;
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

JobQueryModel *LlqCommandManagerPrivate::buildLlqQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    // 不能直接对每行使用trimmed，因为第一项和最后一项都可能为空，trimmed将破坏数据。
//    std::transform(lines.begin(), lines.end(),
//                   lines.begin(), [=](QString str){
//        return str.trimmed();
//    });

    return JobQueryModel::buildFromLlqQueryResponse(lines);
}

JobQueryModel *LlqCommandManagerPrivate::buildLlqDetailQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    return JobQueryModel::buildFromLlqDetailQueryResponse(lines);
}

bool LlqCommandManagerPrivate::isLlqDetailQuery(const QString &command, const QStringList &arguments) const
{
    Q_UNUSED(arguments);
    if(command.indexOf("-l") == -1)
        return false;
    else
        return true;
}
