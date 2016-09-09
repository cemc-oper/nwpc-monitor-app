#pragma once

#include "../loadleveler_monitor_global.h"
#include "model_constants.h"

#include "query_record_parser.h"
#include "query_item_value_saver.h"

#include <QString>
#include <QVector>
#include <QStringList>
#include <QtDebug>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QVariantList>

#include <tuple>
#include <vector>

namespace LoadLevelerMonitor{

namespace Model{

enum class QueryType{
    UnknownQuery,
    LlqDefaultQuery,
    LlqDetailQuery,
    LlclassDefaultQuery,
    LlclassDetailQuery
};

LOADLEVELER_MONITOR_EXPORT QDebug operator <<(QDebug debug, const QueryValueType &value_type);

LOADLEVELER_MONITOR_EXPORT QVector<int> getCategoryColumnWidth(const QString &mark_line);


// id, display_name_, label, type, command_line_, parser_name, parser_arguments
using DefaultQueryCategoryType =
    std::tuple<QString, QString, QString, QueryValueType, QString, QString, QVariantList>;

struct LOADLEVELER_MONITOR_EXPORT QueryCategory
{
public:
    static const QString kValidId;

    QueryCategory():
        id_                 {kValidId},
        display_name_       {""},
        label_              {""},
        value_saver_        {new QueryItemValueSaver},
        category_type_      {QueryType::UnknownQuery},
        record_parser_type_ {""},
        command_line_       {""}
    {
    }
    QueryCategory(const QueryCategory &other):
        id_                 {other.id_},
        display_name_       {other.display_name_},
        label_              {other.label_},
        value_saver_        {other.value_saver_},
        category_type_      {other.category_type_},
        record_parser_type_ {other.record_parser_type_},
        command_line_       {other.command_line_}
    {
        foreach(QVariant args, other.record_parser_args_)
        {
            record_parser_args_.append(args);
        }
        record_parser_.reset(QueryRecordParserFactory::make(other.record_parser_type_, other.record_parser_args_));
    }

    QueryCategory& operator=(const QueryCategory &other)
    {
        id_                 = other.id_;
        display_name_       = other.display_name_;
        label_              = other.label_;
        value_saver_        = other.value_saver_;
        category_type_      = other.category_type_;
        record_parser_type_ = other.record_parser_type_;

        record_parser_args_.clear();
        foreach(QVariant args, other.record_parser_args_)
        {
            record_parser_args_.append(args);
        }
        record_parser_.reset(QueryRecordParserFactory::make(record_parser_type_, record_parser_args_));
        command_line_       = other.command_line_;
        return *this;
    }

    ~QueryCategory(){}

    virtual bool isValid();
    bool operator ==(const QueryCategory &other);

public:
    QString id_;
    QString display_name_; // step id
    QString label_; // Step Id

    // parser: record => value
    QueryType category_type_;

    QString record_parser_type_;
    QVariantList record_parser_args_;
    QScopedPointer<QueryRecordParser> record_parser_;

    // saver: value => item
    QSharedPointer<QueryItemValueSaver> value_saver_; // use QueryValueType to make from factory,

    // llq query
    QString command_line_; // %id

public:
    static QueryCategory createLlqDefaultQueryCategory();
    static QueryCategory createLlqDefaultQueryCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlqDetialQueryCategory();
    static QueryCategory createLlqDetialQueryCategory(const DefaultQueryCategoryType &record);

    static QueryCategory createLlclassDefaultCategory();
    static QueryCategory createLlclassDefaultCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlclassDetailCategory();
    static QueryCategory createLlclassDetailCategory(const DefaultQueryCategoryType &record);

    static QueryCategory createCateogry(const DefaultQueryCategoryType &record);
    static QueryCategory createDefaultQueryCategory();
    static QueryCategory createDetialQueryCategory();
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
    std::make_tuple(Constant::Llq::Id,                  "Id",                   "Job Step Id",      QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Job Step Id"}   ),
    std::make_tuple(Constant::Llq::Owner,               "Owner",                "Owner",            QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Owner"}   ),
    std::make_tuple(Constant::Llq::Class,               "Class",                "Class",            QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Class"}   ),
    std::make_tuple(Constant::Llq::JobScript,           "Job Script",           "Executable",       QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Executable"}   ),
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::JobState,   "",     kDetailLabelParser,    QVariantList{"Status"}   ),
    std::make_tuple(Constant::Llq::QueueFullDate,       "Queue Date",           "Queue Date",       QueryValueType::FullDate,   "",     kDetailLabelParser,    QVariantList{"Queue Date"}   ),
    std::make_tuple(Constant::Llq::NodeMinimum,         "Node Minimun",         "Node minimum",     QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"Node minimum"}   ),
    std::make_tuple(Constant::Llq::NodeActual,          "Node Actual",          "Node actual",      QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"Node actual"}   ),
    std::make_tuple(Constant::Llq::TaskInstanceCount,   "Task Instance Count",  "Num Task Inst",    QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"Num Task Inst"}   ),
  //std::make_tuple(Constant::Llq::StepType,            "Step Type",            "Step Type",        QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Step Type"}   ),       // Serial | General Parallel

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llq::No,                 "No.",                  "No.",               QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"No."}   )    // row number in result records
};

const std::vector<DefaultQueryCategoryType> kLlclassDefaultQueryCategoryList = {
    std::make_tuple(Constant::Llclass::Name,           "Name",                 "Name",                 QueryValueType::String,  "",     kQueryTableRecordParser,    QVariantList{}    ),
    std::make_tuple(Constant::Llclass::MaxJobCpu,      "Max Job Cpu",          "MaxJobCPUd+hh:mm:ss",  QueryValueType::String,  "",     kQueryTableRecordParser,    QVariantList{}    ),
    std::make_tuple(Constant::Llclass::MaxProcCpu,     "Max Proc Cpu",         "MaxProcCPUd+hh:mm:ss", QueryValueType::String,  "",     kQueryTableRecordParser,    QVariantList{}    ),
    std::make_tuple(Constant::Llclass::FreeSlots,      "Free Slots",           "FreeSlots",            QueryValueType::String,  "",     kQueryTableRecordParser,    QVariantList{}    ),
    std::make_tuple(Constant::Llclass::MaxSlots,       "Max Slots",            "MaxSlots",             QueryValueType::String,  "",     kQueryTableRecordParser,    QVariantList{}    ),
    std::make_tuple(Constant::Llclass::Description,    "Description",          "Description",          QueryValueType::String,  "",     kQueryTableRecordParser,    QVariantList{}    ),

    // additional categories not used in command argument.
    std::make_tuple(Constant::Llclass::No,             "No.",                  "No.",                  QueryValueType::Number,  "",     kQueryTableRecordParser,    QVariantList{}   )    // row number in result records
};

const std::vector<DefaultQueryCategoryType> kLlclassDetailQueryCategoryList = {
    std::make_tuple(Constant::Llclass::Name,               "Name",             "Name",                 QueryValueType::String,  "",     kDetailLabelParser,    QVariantList{"Name"}    ),
    std::make_tuple(Constant::Llclass::ExcludeUsers,       "Exclude Users",    "Exclude_Users",        QueryValueType::String,  "",     kDetailLabelParser,    QVariantList{"Exclude_Users"}    ),
    std::make_tuple(Constant::Llclass::IncludeUsers,       "Include Users",    "Include_Users",        QueryValueType::String,  "",     kDetailLabelParser,    QVariantList{"Include_Users"}    ),
    std::make_tuple(Constant::Llclass::WallColockLimit,    "Wall clock limit", "Wall_clock_limit",     QueryValueType::String,  "",     kDetailLabelParser,    QVariantList{"Wall_clock_limit"}    ),
    std::make_tuple(Constant::Llclass::FreeSlots,          "Free Slots",       "Free_slots",           QueryValueType::String,  "",     kDetailLabelParser,    QVariantList{"Free_slots"}    ),
    std::make_tuple(Constant::Llclass::MaxSlots,           "Max Slots",        "Maximum_slots",        QueryValueType::String,  "",     kDetailLabelParser,    QVariantList{"Maximum_slots"}    ),

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llclass::No,                 "No.",                  "No.",              QueryValueType::Number,  "",     kDetailLabelParser,    QVariantList{"No."}    )    // row number in result records
};

}

}
