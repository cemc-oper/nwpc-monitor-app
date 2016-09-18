#include "llq_command_manager_private.h"

#include "llq_command_manager.h"
#include "query_item.h"
#include "query_model.h"
#include "query_util.h"

#include "../chart/category_model_processor.h"
#include "../chart/processor_condition.h"
#include "../chart/model_processor.h"

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>

#include <vector>
#include <algorithm>

using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;

const std::vector<DefaultQueryCategoryType> kLlqDefaultQueryCategoryList = {
    //              id,                            display_name_,              label,          type                        command_line_,

    // used in default llq output
    std::make_tuple(Constant::Llq::Id,             "Id",                       "Id",           QueryValueType::String,      "",     kQueryTableRecordParser,    QVariantList{}  ),// cma20n04.2681148.0
    std::make_tuple(Constant::Llq::Submitted,      "Submitted",                "Submitted",    QueryValueType::Date,        "",     kQueryTableRecordParser,    QVariantList{}  ),// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    std::make_tuple(Constant::Llq::Class,          "Class",                    "Class",        QueryValueType::String,      "%c" ,  kQueryTableRecordParser,    QVariantList{}  ),// normal|operation
    std::make_tuple(Constant::Llq::DispatchDate,   "Dispatch Date",            "Disp. Date",   QueryValueType::Date,        "%dd",  kQueryTableRecordParser,    QVariantList{}  ),// 08/20 12:37
    std::make_tuple(Constant::Llq::QueueDate,      "Queue Date",               "Queue Date",   QueryValueType::Date,        "%dq",  kQueryTableRecordParser,    QVariantList{}  ),// 08/20 12:37
    std::make_tuple(Constant::Llq::UnixGroup,      "UNIX Group",               "Unix Group",   QueryValueType::String,      "%gu",  kQueryTableRecordParser,    QVariantList{}  ),// eps
    std::make_tuple(Constant::Llq::HostName,       "Running On",               "Running On",   QueryValueType::String,      "%h",   kQueryTableRecordParser,    QVariantList{}  ),// cma19n06
    std::make_tuple(Constant::Llq::StepId,         "Step Id",                  "Step Id",      QueryValueType::String,      "%id",  kQueryTableRecordParser,    QVariantList{}  ),// cma20n04.2681148.0
    std::make_tuple(Constant::Llq::ImageSize,      "Virtual Image Size",       "Im.Size",      QueryValueType::Number,      "%is",  kQueryTableRecordParser,    QVariantList{}  ),// 13
    std::make_tuple(Constant::Llq::JobName,        "Job Name",                 "Job Name",     QueryValueType::String,      "%jn",  kQueryTableRecordParser,    QVariantList{}  ),// cma20n04.2681148
    std::make_tuple(Constant::Llq::JobType,        "Job Type",                 "Type",         QueryValueType::String,      "%jt",  kQueryTableRecordParser,    QVariantList{}  ),// SER|PAR
    std::make_tuple(Constant::Llq::HostCount,      "Number of Hosts",          "NM",           QueryValueType::Number,      "%nh",  kQueryTableRecordParser,    QVariantList{}  ),// 16
    std::make_tuple(Constant::Llq::Owner,          "Job Owner",                "Owner",        QueryValueType::String,      "%o" ,  kQueryTableRecordParser,    QVariantList{}  ),// nwp_qu
    std::make_tuple(Constant::Llq::Priority,       "User Priority",            "PRI",          QueryValueType::Number,      "%p" ,  kQueryTableRecordParser,    QVariantList{}  ),// 50
    std::make_tuple(Constant::Llq::StepName,       "Step Name",                "Step Name",    QueryValueType::String,      "%sn",  kQueryTableRecordParser,    QVariantList{}  ),// 0
    std::make_tuple(Constant::Llq::Status,         "Status",                   "ST",           QueryValueType::JobState,    "%st",  kQueryTableRecordParser,    QVariantList{}  ),// R

    // additional categories not used in command argument.
    std::make_tuple(Constant::Llq::No,             "No.",                      "No.",          QueryValueType::Number,      "",     kQueryTableRecordParser,    QVariantList{}  ),    // row number in result records
};

const std::vector<DefaultQueryCategoryType> kLlqDetailQuerySerialJobCategoryList = {
    //              id,                                 display name,           label,              type
    std::make_tuple(Constant::Llq::Id,                  "Id",                   "Job Step Id",      QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Job Step Id"}   ),
    std::make_tuple(Constant::Llq::Owner,               "Owner",                "Owner",            QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Owner"}   ),
    std::make_tuple(Constant::Llq::Class,               "Class",                "Class",            QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Class"}   ),
    std::make_tuple(Constant::Llq::JobScript,           "Job Script",           "Cmd",              QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Cmd"}   ),
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::JobState,   "",     kDetailLabelParser,    QVariantList{"Status"}   ),
    std::make_tuple(Constant::Llq::QueueFullDate,       "Queue Date",           "Queue Date",       QueryValueType::FullDate,   "",     kDetailLabelParser,    QVariantList{"Queue Date"}   ),
  //std::make_tuple(Constant::Llq::StepType,            "Step Type",            "Step Type",        QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Step Type"}   ),       // Serial | General Parallel

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llq::No,                  "No.",                  "No.",              QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"No."}   )    // row number in result records
};

const std::vector<DefaultQueryCategoryType> kLlqDetailQueryParallelCategoryList = {
    //              id,                                 display name,           label,              type
    std::make_tuple(Constant::Llq::Id,                  "Id",                   "Job Step Id",      QueryValueType::String,     "",     kDetailLabelParser,         QVariantList{"Job Step Id"}   ),
    std::make_tuple(Constant::Llq::Owner,               "Owner",                "Owner",            QueryValueType::String,     "",     kDetailLabelParser,         QVariantList{"Owner"}   ),
    std::make_tuple(Constant::Llq::Class,               "Class",                "Class",            QueryValueType::String,     "",     kDetailLabelParser,         QVariantList{"Class"}   ),
    std::make_tuple(Constant::Llq::JobScript,           "Job Script",           "Executable",       QueryValueType::String,     "",     kDetailLabelParser,         QVariantList{"Executable"}   ),
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::JobState,   "",     kDetailLabelParser,         QVariantList{"Status"}   ),
    std::make_tuple(Constant::Llq::QueueFullDate,       "Queue Date",           "Queue Date",       QueryValueType::FullDate,   "",     kDetailLabelParser,         QVariantList{"Queue Date"}   ),
    std::make_tuple(Constant::Llq::NodeMinimum,         "Node Minimun",         "Node minimum",     QueryValueType::Number,     "",     kDetailLabelParser,         QVariantList{"Node minimum"}   ),
    std::make_tuple(Constant::Llq::NodeActual,          "Node Actual",          "Node actual",      QueryValueType::Number,     "",     kDetailLabelParser,         QVariantList{"Node actual"}   ),
    std::make_tuple(Constant::Llq::TaskInstanceCount,   "Task Instance Count",  "Num Task Inst",    QueryValueType::Number,     "",     kTaskInstanceCountParser,   QVariantList{}   ),
  //std::make_tuple(Constant::Llq::StepType,            "Step Type",            "Step Type",        QueryValueType::String,     "",     kDetailLabelParser,         QVariantList{"Step Type"}   ),       // Serial | General Parallel

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llq::No,                 "No.",                  "No.",               QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"No."}   )    // row number in result records
};

LlqCommandManagerPrivate::LlqCommandManagerPrivate(LlqCommandManager *parent) :
    QObject{parent},
    p{parent}
{

}

LlqCommandManagerPrivate::~LlqCommandManagerPrivate()
{

}

void LlqCommandManagerPrivate::initCategoryList()
{
    default_query_category_list_.clear();
    foreach(auto record, kLlqDefaultQueryCategoryList)
    {
        default_query_category_list_.append(QueryCategoryFactory::createLlqDefaultQueryCategory(record));
    }

    serial_job_detail_category_list_.clear();
    foreach(auto record, kLlqDetailQuerySerialJobCategoryList)
    {
        QueryCategory c = QueryCategoryFactory::createLlqDetialQueryCategory(record);
        serial_job_detail_category_list_.append(c);
    }

    parallel_job_detail_category_list_.clear();
    foreach(auto record, kLlqDetailQueryParallelCategoryList)
    {
        QueryCategory c = QueryCategoryFactory::createLlqDetialQueryCategory(record);
        parallel_job_detail_category_list_.append(c);
    }
}

QueryCategory LlqCommandManagerPrivate::findQueryCategory(const QString &label)
{
    if(default_query_category_list_.containsLabel(label))
        return default_query_category_list_.categoryFromLabel(label);
    else
        return QueryCategoryFactory::createLlqDefaultQueryCategory();
}

QueryCategory LlqCommandManagerPrivate::findSerialJobDetailQueryCategory(const QString &label) const
{
    if(serial_job_detail_category_list_.containsLabel(label))
        return serial_job_detail_category_list_.categoryFromLabel(label);
    else
        return QueryCategoryFactory::createLlqDetialQueryCategory();
}

QueryCategory LlqCommandManagerPrivate::findParellelJobDetailQueryCategory(const QString &label) const
{
    if(parallel_job_detail_category_list_.containsLabel(label))
        return parallel_job_detail_category_list_.categoryFromLabel(label);
    else
        return QueryCategoryFactory::createLlqDetialQueryCategory();
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

    // request command
    QJsonObject request = data["request"].toObject();
    QString command = request["command"].toString();
    QJsonArray arguments = request["arguments"].toArray();
    QStringList arg_list;
    foreach(QJsonValue an_argument, arguments)
    {
        arg_list.append(an_argument.toString());
    }

    // response message
    QJsonObject message = data["response"].toObject()["message"].toObject();
    QString output_message = message["output"].toString();
    Q_ASSERT(!output_message.isEmpty());
    QStringList lines = output_message.split('\n');
    // 不能直接对每行使用trimmed，因为第一项和最后一项都可能为空，trimmed将破坏数据。
//    std::transform(lines.begin(), lines.end(),
//                   lines.begin(), [=](QString str){
//        return str.trimmed();
//    });

    // build model
    QueryModel *model = nullptr;
    if(QueryUtil::isDetailQuery(command, arg_list))
    {
        model = QueryModel::buildFromLlqDetailQueryResponse(lines);
    }
    else
    {
        model = QueryModel::buildFromLlqDefaultQueryResponse(lines);
    }

    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] end";
    return model;
}

void LlqCommandManagerPrivate::initModelProcessor()
{
    // condition -> processor
    // register single category count processor
    registerSingleCategoryCountProcessorMap(Constant::Llq::Owner);
    registerSingleCategoryCountProcessorMap(Constant::Llq::Status);
    registerSingleCategoryCountProcessorMap(Constant::Llq::Class);
}


void LlqCommandManagerPrivate::registerSingleCategoryCountProcessorMap(const QString &category_id)
{
    QueryCategory category = default_query_category_list_.categoryFromId(category_id);
    Q_ASSERT(category.isValid());
    QueryCategoryList category_list;
    category_list.append(category);

    CategoryProcessorCondition *condition = new CategoryProcessorCondition{category_list};
    SingleCategorCountProcessor *processor = new SingleCategorCountProcessor{category_list};
    processor->setDisplayName(category_list[0].display_name_);
    registerProcessorMap(condition, processor);
}

void LlqCommandManagerPrivate::registerProcessorMap(ProcessorCondition *condition, ModelProcessor *processor)
{
    processor_list_.insert(processor);
    processor_condition_list_.insert(condition);
    processor_map_.insert(condition, processor);
}
