#include "llq_command_manager_private.h"

#include "llq_command_manager.h"
#include "query_item.h"
#include "query_model.h"

#include "../chart/model_category_processor.h"

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>

#include <algorithm>

using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;

LlqCommandManagerPrivate::LlqCommandManagerPrivate(LlqCommandManager *parent) :
    QObject{parent},
    p{parent},
    model_data_processor_{nullptr}
{

}

void LlqCommandManagerPrivate::initLlqCategoryList()
{
    default_query_category_list_.clear();
    foreach(QStringList record, kLlqDefaultQueryCategoryList)
    {
        default_query_category_list_.append(QueryCategory::createFromStringList(record));
    }

    serial_job_detail_category_list_.clear();
    foreach(QStringList record, kLlqDetailQuerySerialJobCategoryList)
    {
        QueryCategory c = QueryCategory::createFromStringList(record);
        serial_job_detail_category_list_.append(c);
    }

    parallel_job_detail_category_list_.clear();
    foreach(QStringList record, kLlqDetailQueryParallelCategoryList)
    {
        QueryCategory c = QueryCategory::createFromStringList(record);
        parallel_job_detail_category_list_.append(c);
    }
}

QueryCategory LlqCommandManagerPrivate::findQueryCategory(const QString result_title)
{
    QueryCategory result_category;
    for(int i=0; i<default_query_category_list_.length(); i++)
    {
        QueryCategory category = default_query_category_list_[i];
        if( category.label_ == result_title )
        {
            result_category = category;
            break;
        }
    }
    return result_category;
}

QueryCategory LlqCommandManagerPrivate::findSerialJobDetailQueryCategory(const QString &label) const
{
    if(serial_job_detail_category_list_.containsLabel(label))
        return serial_job_detail_category_list_.categoryFromLabel(label);
    else
        return QueryCategory();
}

QueryCategory LlqCommandManagerPrivate::findParellelJobDetailQueryCategory(const QString &label) const
{
    if(parallel_job_detail_category_list_.containsLabel(label))
        return parallel_job_detail_category_list_.categoryFromLabel(label);
    else
        return QueryCategory();
}

QueryModel *LlqCommandManagerPrivate::buildQueryModelFromResponse(const QString &response_str)
{
    QJsonDocument doc = QJsonDocument::fromJson(response_str.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] result is not a json string.";
        return nullptr;
    }

    return buildQueryModelFromResponse(doc);
}

QueryModel *LlqCommandManagerPrivate::buildQueryModelFromResponse(const QJsonDocument &response_json_document)
{
    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] start";
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
    if(isDetailQuery(command, arg_list))
    {
        model = buildDetailQueryModel(output_message);
    }
    else
    {
        model = buildDefaultQueryModel(output_message);
    }

    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] end";
    return model;
}

void LlqCommandManagerPrivate::initModelDataProcessor()
{
    model_data_processor_ = new ModelCategoryProcessor{this};
}

ModelCategoryProcessor *LlqCommandManagerPrivate::modelDataProcessor()
{
    return model_data_processor_;
}

QueryModel *LlqCommandManagerPrivate::buildDefaultQueryModel(const QString &output)
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

QueryModel *LlqCommandManagerPrivate::buildDetailQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    return QueryModel::buildFromLlqDetailQueryResponse(lines);
}

bool LlqCommandManagerPrivate::isDetailQuery(const QString &command, const QStringList &arguments) const
{
    Q_UNUSED(arguments);
    if(command.indexOf("-l") == -1)
        return false;
    else
        return true;
}
