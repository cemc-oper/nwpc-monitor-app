#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QVector>
#include <QStringList>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

enum class QueryType{
    UnknownQuery,
    LlqDefaultQuery,
    LlqDetailQuery,
    LlclassDefaultQuery,
    LlclassDetailQuery
};

struct LOADLEVELER_MONITOR_EXPORT QueryCategory
{
public:
    static const QString VALID_ID;

    struct ValueType{
        static const QString Unknown;
        static const QString String;
        static const QString Number;
        static const QString Date;
        static const QString FullDate;
    };

    QueryCategory();

    bool isValid();
    bool operator ==(const QueryCategory &other);

    static QueryCategory createFromStringList(QStringList record);

    QString id_;
    QString display_name_; // step id
    QString label_; // Step Id
    QString value_type_; // string or number,

    QueryType category_type_;

    // llq query
    QString command_line_; // %id
    int token_length_; // length in output line
};

static const QVector<QStringList> kLlqDefaultQueryCategoryList = {
    // id,              display_name_,      label,          type            command_line_,

    // used in default llq output
    {"id",              "Id",               "Id",           QueryCategory::ValueType::String,    ""              },// cma20n04.2681148.0
    {"submitted",       "Submitted",        "Submitted",    QueryCategory::ValueType::Date,      "",             },// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {"class",           "Class",            "Class",        QueryCategory::ValueType::String,    "%c",           },// normal|operation
    {"dispatch_date",   "Dispatch Date",    "Disp. Date",   QueryCategory::ValueType::Date,      "%dd",          },// 08/20 12:37
    {"queue_date",      "Queue Date",       "Queue Date",   QueryCategory::ValueType::Date,      "%dq",          },// 08/20 12:37
    {"unix_group",      "UNIX Group",       "Unix Group",   QueryCategory::ValueType::String,    "%gu",          },// eps
    {"host_name",       "Running On",       "Running On",   QueryCategory::ValueType::String,    "%h",           },// cma19n06
    {"step_id",         "Step Id",          "Step Id",      QueryCategory::ValueType::String,    "%id",          },// cma20n04.2681148.0
    {"image_size",      "Virtual Image Size""Im.Size",      QueryCategory::ValueType::Number,    "%is",          },// 13
    {"job_name",        "Job Name",         "Job Name",     QueryCategory::ValueType::String,    "%jn",          },// cma20n04.2681148
    {"job_type",        "Job Type",         "Type",         QueryCategory::ValueType::String,    "%jt",          },// SER|PAR
    {"host_count",      "Number of Hosts",  "NM",           QueryCategory::ValueType::Number,    "%nh",          },// 16
    {"owner",           "Job Owner",        "Owner",        QueryCategory::ValueType::String,    "%o",           },// nwp_qu
    {"priority",        "User Priority",    "PRI",          QueryCategory::ValueType::Number,    "%p",           },// 50
    {"step_name",       "Step Name",        "Step Name",    QueryCategory::ValueType::String,    "%sn",          },// 0
    {"status",          "Status",           "ST",           QueryCategory::ValueType::String,    "%st",          },// R

    // additional categories not used in command argument.
    {"no",              "No.",              "No.",          QueryCategory::ValueType::Number,    "",             }    // row number in result records
};


static const QVector<QStringList> kLlqDetailQuerySerialJobCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      QueryCategory::ValueType::String},
    {"owner",           "Owner",            "Owner",            QueryCategory::ValueType::String},
    {"queue_full_date", "Queue Date",       "Queue Date",       QueryCategory::ValueType::FullDate},
    {"status",          "Status",           "Status",           QueryCategory::ValueType::String},
    {"class",           "Class",            "Class",            QueryCategory::ValueType::String},
    //{"step_type",       "Step Type",        "Step Type",        LlqQueryCategory::ValueType::String},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Cmd",              QueryCategory::ValueType::String}
};

static const QVector<QStringList> kLlqDetailQueryParallelCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      QueryCategory::ValueType::String},
    {"owner",           "Owner",            "Owner",            QueryCategory::ValueType::String},
    {"queue_full_date", "Queue Date",       "Queue Date",       QueryCategory::ValueType::FullDate},
    {"status",          "Status",           "Status",           QueryCategory::ValueType::String},
    {"class",           "Class",            "Class",            QueryCategory::ValueType::String},
    //{"step_type",       "Step Type",        "Step Type",        LlqQueryCategory::ValueType::String},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Executable",       QueryCategory::ValueType::String},
    {"num_task_inst",   "Num Task Inst",    "Num Task Inst",    QueryCategory::ValueType::Number},
};


}

}
