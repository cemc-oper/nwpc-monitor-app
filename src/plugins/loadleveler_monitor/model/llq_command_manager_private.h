#pragma once

#include "query_category.h"
#include "query_category_list.h"

#include <QHash>
#include <QMultiMap>
#include <QSet>
#include <QObject>

namespace LoadLevelerMonitor{

namespace Chart{
class CategoryModelProcessor;
class ProcessorCondition;
class ModelProcessor;
}

namespace Model{

class LlqCommandManager;
class QueryModel;

class LlqCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlqCommandManagerPrivate(LlqCommandManager *parent = 0);
    ~LlqCommandManagerPrivate();

    void initCategoryList();

    QueryCategory findQueryCategory(const QString &label);
    QueryCategory findSerialJobDetailQueryCategory(const QString &label) const;
    QueryCategory findParellelJobDetailQueryCategory(const QString &label) const;

    QueryModel *buildQueryModelFromResponse(const QString &response_str);
    QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_json_document);

    void initModelProcessor();

    QSet<Chart::ModelProcessor*> &processorList(){
        return processor_list_;
    }

    QSet<Chart::ProcessorCondition*> &processorConditionList(){
        return processor_condition_list_;
    }

    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> &processorMap(){
        return processor_map_;
    }

signals:

public slots:

private:
    void registerSingleCategoryCountProcessorMap(const QString &category_id);
    void registerProcessorMap(Chart::ProcessorCondition* condition, Chart::ModelProcessor* processor);

    LlqCommandManager *p;

    QueryCategoryList default_query_category_list_;
    QueryCategoryList serial_job_detail_category_list_;
    QueryCategoryList parallel_job_detail_category_list_;

    QSet<Chart::ModelProcessor*> processor_list_;
    QSet<Chart::ProcessorCondition*> processor_condition_list_;
    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> processor_map_;

    friend class LlqCommandManager;
};

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

}

}
