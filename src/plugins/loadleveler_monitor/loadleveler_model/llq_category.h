#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QVector>
#include <QStringList>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{


struct LOADLEVELER_MONITOR_EXPORT LlqQueryCategory
{
public:
    enum class CategoryType{
        NormalQuery,
        DetailQuery
    };

    static const QString VALID_ID;

    struct ValueType{
        static const QString Unknown;
        static const QString String;
        static const QString Number;
        static const QString Date;
        static const QString FullDate;
    };

    LlqQueryCategory();

    bool isValid();
    bool operator ==(const LlqQueryCategory &other);

    static LlqQueryCategory createFromStringList(QStringList record);

    QString id_;
    QString display_name_; // step id
    QString label_; // Step Id
    QString value_type_; // string or number,

    CategoryType category_type_;

    // llq query
    QString command_line_; // %id
    int token_length_; // length in output line
};

static const QVector<QStringList> LLQ_QUERY_CATEGARY_LIST = {
    // id,              display_name_,      label,          type            command_line_,

    // used in default llq output
    {"id",              "Id",               "Id",           LlqQueryCategory::ValueType::String,    ""              },// cma20n04.2681148.0
    {"submitted",       "Submitted",        "Submitted",    LlqQueryCategory::ValueType::Date,      "",             },// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {"class",           "Class",            "Class",        LlqQueryCategory::ValueType::String,    "%c",           },// normal|operation
    {"dispatch_date",   "Dispatch Date",    "Disp. Date",   LlqQueryCategory::ValueType::Date,      "%dd",          },// 08/20 12:37
    {"queue_date",      "Queue Date",       "Queue Date",   LlqQueryCategory::ValueType::Date,      "%dq",          },// 08/20 12:37
    {"unix_group",      "UNIX Group",       "Unix Group",   LlqQueryCategory::ValueType::String,    "%gu",          },// eps
    {"host_name",       "Running On",       "Running On",   LlqQueryCategory::ValueType::String,    "%h",           },// cma19n06
    {"step_id",         "Step Id",          "Step Id",      LlqQueryCategory::ValueType::String,    "%id",          },// cma20n04.2681148.0
    {"image_size",      "Virtual Image Size""Im.Size",      LlqQueryCategory::ValueType::Number,    "%is",          },// 13
    {"job_name",        "Job Name",         "Job Name",     LlqQueryCategory::ValueType::String,    "%jn",          },// cma20n04.2681148
    {"job_type",        "Job Type",         "Type",         LlqQueryCategory::ValueType::String,    "%jt",          },// SER|PAR
    {"host_count",      "Number of Hosts",  "NM",           LlqQueryCategory::ValueType::Number,    "%nh",          },// 16
    {"owner",           "Job Owner",        "Owner",        LlqQueryCategory::ValueType::String,    "%o",           },// nwp_qu
    {"priority",        "User Priority",    "PRI",          LlqQueryCategory::ValueType::Number,    "%p",           },// 50
    {"step_name",       "Step Name",        "Step Name",    LlqQueryCategory::ValueType::String,    "%sn",          },// 0
    {"status",          "Status",           "ST",           LlqQueryCategory::ValueType::String,    "%st",          },// R

    // additional categories not used in command argument.
    {"no",              "No.",              "No.",          LlqQueryCategory::ValueType::Number,    "",             }    // row number in result records
};


static const QVector<QStringList> kLlqDetailQuerySerialJobCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      LlqQueryCategory::ValueType::String},
    {"owner",           "Owner",            "Owner",            LlqQueryCategory::ValueType::String},
    {"queue_full_date", "Queue Date",       "Queue Date",       LlqQueryCategory::ValueType::FullDate},
    {"status",          "Status",           "Status",           LlqQueryCategory::ValueType::String},
    {"class",           "Class",            "Class",            LlqQueryCategory::ValueType::String},
    //{"step_type",       "Step Type",        "Step Type",        LlqQueryCategory::ValueType::String},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Cmd",              LlqQueryCategory::ValueType::String}
};

static const QVector<QStringList> kLlqDetailQueryParallelCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      LlqQueryCategory::ValueType::String},
    {"owner",           "Owner",            "Owner",            LlqQueryCategory::ValueType::String},
    {"queue_full_date", "Queue Date",       "Queue Date",       LlqQueryCategory::ValueType::FullDate},
    {"status",          "Status",           "Status",           LlqQueryCategory::ValueType::String},
    {"class",           "Class",            "Class",            LlqQueryCategory::ValueType::String},
    //{"step_type",       "Step Type",        "Step Type",        LlqQueryCategory::ValueType::String},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Executable",       LlqQueryCategory::ValueType::String},
    {"num_task_inst",   "Num Task Inst",    "Num Task Inst",    LlqQueryCategory::ValueType::Number},
};


}

}
