#pragma once

#include "../loadleveler_monitor_global.h"
#include "model_constants.h"

#include <QString>
#include <QVector>
#include <QStringList>
#include <QtDebug>

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

enum class QueryValueType{
    Unknown,
    String,
    Number,
    Date,       // 'MM/DD HH:MM'
    FullDate    // Mon Aug 22 02:25:09 2016
};

LOADLEVELER_MONITOR_EXPORT QDebug operator <<(QDebug debug, const QueryValueType &value_type);

struct QueryCategory
{
public:
    static const QString kValidId;

    QueryCategory():
        id_{kValidId},
        display_name_{""},
        label_{""},
        value_type_{QueryValueType::Unknown},
        category_type_{QueryType::UnknownQuery},
        command_line_{""},
        token_length_{-1}
    {

    }

    QueryCategory(const QueryCategory &other):
        id_{other.id_},
        display_name_{other.display_name_},
        label_{other.label_},
        value_type_{other.value_type_},
        category_type_{other.category_type_},
        command_line_{other.command_line_},
        token_length_{other.token_length_}
    {

    }

    virtual ~QueryCategory(){}

    virtual bool isValid();
    bool operator ==(const QueryCategory &other);

    static QueryCategory createLlqDefaultQueryCategory(const std::tuple<QString, QString, QString, QueryValueType, QString> &record);
    static QueryCategory createLlqDetialQueryCategory(const std::tuple<QString, QString, QString, QueryValueType> &record);
    static QueryCategory createLlclassDefaultCategory(const std::tuple<QString, QString, QString, QueryValueType> &record);
    static QueryCategory createLlclassDetailCategory(const std::tuple<QString, QString, QString, QueryValueType> &record);

    QString id_;
    QString display_name_; // step id
    QString label_; // Step Id
    QueryValueType value_type_; // string or number,
    QueryType category_type_;

    // llq query
    QString command_line_; // %id
    int token_length_; // length in output line
};

const std::vector< std::tuple<QString, QString, QString, QueryValueType, QString> > kLlqDefaultQueryCategoryList = {
    //              id,                            display_name_,              label,          type                        command_line_,

    // used in default llq output
    std::make_tuple(Constant::Llq::Id,             "Id",                       "Id",           QueryValueType::String,      ""              ),// cma20n04.2681148.0
    std::make_tuple(Constant::Llq::Submitted,      "Submitted",                "Submitted",    QueryValueType::Date,        ""              ),// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    std::make_tuple(Constant::Llq::Class,          "Class",                    "Class",        QueryValueType::String,      "%c"            ),// normal|operation
    std::make_tuple(Constant::Llq::DispatchDate,   "Dispatch Date",            "Disp. Date",   QueryValueType::Date,        "%dd"           ),// 08/20 12:37
    std::make_tuple(Constant::Llq::QueueDate,      "Queue Date",               "Queue Date",   QueryValueType::Date,        "%dq"           ),// 08/20 12:37
    std::make_tuple(Constant::Llq::UnixGroup,      "UNIX Group",               "Unix Group",   QueryValueType::String,      "%gu"           ),// eps
    std::make_tuple(Constant::Llq::HostName,       "Running On",               "Running On",   QueryValueType::String,      "%h"            ),// cma19n06
    std::make_tuple(Constant::Llq::StepId,         "Step Id",                  "Step Id",      QueryValueType::String,      "%id"           ),// cma20n04.2681148.0
    std::make_tuple(Constant::Llq::ImageSize,      "Virtual Image Size",       "Im.Size",      QueryValueType::Number,      "%is"           ),// 13
    std::make_tuple(Constant::Llq::JobName,        "Job Name",                 "Job Name",     QueryValueType::String,      "%jn"           ),// cma20n04.2681148
    std::make_tuple(Constant::Llq::JobType,        "Job Type",                 "Type",         QueryValueType::String,      "%jt"           ),// SER|PAR
    std::make_tuple(Constant::Llq::HostCount,      "Number of Hosts",          "NM",           QueryValueType::Number,      "%nh"           ),// 16
    std::make_tuple(Constant::Llq::Owner,          "Job Owner",                "Owner",        QueryValueType::String,      "%o"            ),// nwp_qu
    std::make_tuple(Constant::Llq::Priority,       "User Priority",            "PRI",          QueryValueType::Number,      "%p"            ),// 50
    std::make_tuple(Constant::Llq::StepName,       "Step Name",                "Step Name",    QueryValueType::String,      "%sn"           ),// 0
    std::make_tuple(Constant::Llq::Status,         "Status",                   "ST",           QueryValueType::String,      "%st"           ),// R

    // additional categories not used in command argument.
    std::make_tuple(Constant::Llq::No,             "No.",                      "No.",          QueryValueType::Number,      ""              ),    // row number in result records
};


const std::vector<std::tuple<QString, QString, QString, QueryValueType>> kLlqDetailQuerySerialJobCategoryList = {
    //              id,                                 display name,           label,              type
    std::make_tuple(Constant::Llq::Id,                  "Id",                   "Job Step Id",      QueryValueType::String      ),
    std::make_tuple(Constant::Llq::Owner,               "Owner",                "Owner",            QueryValueType::String      ),
    std::make_tuple(Constant::Llq::Class,               "Class",                "Class",            QueryValueType::String      ),
    std::make_tuple(Constant::Llq::JobScript,           "Job Script",           "Cmd",              QueryValueType::String      ),
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::String      ),
    std::make_tuple(Constant::Llq::QueueFullDate,       "Queue Date",           "Queue Date",       QueryValueType::FullDate    ),
  //std::make_tuple(Constant::Llq::StepType,            "Step Type",            "Step Type",        QueryValueType::String      ),       // Serial | General Parallel

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llq::No,                  "No.",                  "No.",              QueryValueType::Number,     )    // row number in result records
};

const std::vector<std::tuple<QString, QString, QString, QueryValueType>> kLlqDetailQueryParallelCategoryList = {
    //              id,                                 display name,           label,              type
    std::make_tuple(Constant::Llq::Id,                  "Id",                   "Job Step Id",      QueryValueType::String      ),
    std::make_tuple(Constant::Llq::Owner,               "Owner",                "Owner",            QueryValueType::String      ),
    std::make_tuple(Constant::Llq::Class,               "Class",                "Class",            QueryValueType::String      ),
    std::make_tuple(Constant::Llq::JobScript,           "Job Script",           "Executable",       QueryValueType::String      ),
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::String      ),
    std::make_tuple(Constant::Llq::QueueFullDate,       "Queue Date",           "Queue Date",       QueryValueType::FullDate    ),
    std::make_tuple(Constant::Llq::NodeMinimum,         "Node Minimun",         "Node minimum",     QueryValueType::Number      ),
  //std::make_tuple(Constant::Llq::StepType,            "Step Type",            "Step Type",        QueryValueType::String      ),       // Serial | General Parallel

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llq::No,                 "No.",                  "No.",              QueryValueType::Number,     )    // row number in result records
};

const std::vector<std::tuple<QString, QString, QString, QueryValueType>> kLlclassDefaultQueryCategoryList = {
    std::make_tuple(Constant::Llclass::Name,           "Name",                 "Name",                 QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::MaxJobCpu,      "Max Job Cpu",          "MaxJobCPUd+hh:mm:ss",  QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::MaxProcCpu,     "Max Proc Cpu",         "MaxProcCPUd+hh:mm:ss", QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::FreeSlots,      "Free Slots",           "FreeSlots",            QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::MaxSlots,       "Max Slots",            "MaxSlots",             QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::Description,    "Description",          "Description",          QueryValueType::String      ),

    // additional categories not used in command argument.
    std::make_tuple(Constant::Llclass::No,             "No.",                  "No.",                  QueryValueType::Number      )    // row number in result records
};

const std::vector<std::tuple<QString, QString, QString, QueryValueType>> kLlclassDetailQueryCategoryList = {
    std::make_tuple(Constant::Llclass::Name,               "Name",             "Name",                 QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::ExcludeUsers,       "Exclude Users",    "Exclude_Users",        QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::IncludeUsers,       "Include Users",    "Include_Users",        QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::WallColockLimit,    "Wall clock limit", "Wall_clock_limit",     QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::FreeSlots,          "Free Slots",       "Free_slots",           QueryValueType::String      ),
    std::make_tuple(Constant::Llclass::MaxSlots,           "Max Slots",        "Maximum_slots",        QueryValueType::String      ),

    // additional categories not used in command argument.
  //std::make_tuple(Constant::Llclass::No,                 "No.",                  "No.",          QueryValueType::Number,     )    // row number in result records
};

}

}
