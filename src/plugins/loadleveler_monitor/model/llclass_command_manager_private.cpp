#include "llclass_command_manager_private.h"

#include "llclass_command_manager.h"
#include "query_item.h"
#include "query_model.h"

#include "../chart/category_model_processor.h"
#include "../chart/processor_condition.h"
#include "../chart/model_processor.h"
#include "../chart/percent_bar_processor.h"

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

LlclassCommandManagerPrivate::LlclassCommandManagerPrivate(LlclassCommandManager *parent) :
    QObject{parent},
    p{parent}
{

}

LlclassCommandManagerPrivate::~LlclassCommandManagerPrivate()
{

}

void LlclassCommandManagerPrivate::initCategoryList()
{
    default_query_category_list_.clear();
    foreach(auto record, kLlclassDefaultQueryCategoryList)
    {
        default_query_category_list_.append(QueryCategory::createLlclassDefaultCategory(record));
    }

    detail_query_category_list_.clear();
    foreach(auto record, kLlclassDetailQueryCategoryList)
    {
        QueryCategory c = QueryCategory::createLlclassDetailCategory(record);
        detail_query_category_list_.append(c);
    }
}

QueryCategory LlclassCommandManagerPrivate::findDefaultQueryCategory(const QString result_title)
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

QueryCategory LlclassCommandManagerPrivate::findDetailQueryCategory(const QString &label) const
{
    if(detail_query_category_list_.containsLabel(label))
        return detail_query_category_list_.categoryFromLabel(label);
    else
        return QueryCategory();
}

QueryModel *LlclassCommandManagerPrivate::buildQueryModelFromResponse(const QString &response_str)
{
    QJsonDocument doc = QJsonDocument::fromJson(response_str.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlclassCommandManagerPrivate::buildLlclassQueryModelFromResponse] result is not a json string.";
        return nullptr;
    }

    return buildQueryModelFromResponse(doc);
}

QueryModel *LlclassCommandManagerPrivate::buildQueryModelFromResponse(const QJsonDocument &response_json_document)
{
    qDebug()<<"[LlclassCommandManagerPrivate::buildLlclassQueryModelFromResponse] start";
    QJsonObject result_object = response_json_document.object();

    if( result_object.contains("error"))
    {
        QString error_message = result_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LlclassCommandManagerPrivate::buildLlclassQueryModelFromResponse] ERROR:"<<error_message;
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

    qDebug()<<"[LlclassCommandManagerPrivate::buildLlclassQueryModelFromResponse] end";
    return model;
}

void LlclassCommandManagerPrivate::initModelProcessor()
{
    // condition -> processor
    QueryCategory item_category = default_query_category_list_.categoryFromId("llclass.name");
    QueryCategory total_category = default_query_category_list_.categoryFromId("llclass.max_slots");
    QueryCategory free_category = default_query_category_list_.categoryFromId("llclass.free_slots");
    Q_ASSERT(item_category.isValid());
    Q_ASSERT(total_category.isValid());
    Q_ASSERT(free_category.isValid());

    PercentBarProcessorCondition *condition = new PercentBarProcessorCondition{item_category,total_category,free_category};
    PercentBarProcessor *processor = new PercentBarProcessor{item_category,total_category,free_category};
    processor->setDisplayName("slots");
    registerProcessorMap(condition, processor);
}

QueryModel *LlclassCommandManagerPrivate::buildDefaultQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    // 不能直接对每行使用trimmed，因为第一项和最后一项都可能为空，trimmed将破坏数据。
//    std::transform(lines.begin(), lines.end(),
//                   lines.begin(), [=](QString str){
//        return str.trimmed();
//    });

    return QueryModel::buildFromLlclassDefaultQueryResponse(lines);
}

QueryModel *LlclassCommandManagerPrivate::buildDetailQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    return QueryModel::buildFromLlclassDetailQueryResponse(lines);
}

bool LlclassCommandManagerPrivate::isDetailQuery(const QString &command, const QStringList &arguments) const
{
    Q_UNUSED(arguments);
    if(command.indexOf("-l") == -1)
        return false;
    else
        return true;
}

void LlclassCommandManagerPrivate::registerProcessorMap(ProcessorCondition *condition, ModelProcessor *processor)
{
    processor_list_.insert(processor);
    processor_condition_list_.insert(condition);
    processor_map_.insert(condition, processor);
}
