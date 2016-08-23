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

namespace QueryValueType{
    static const QString Unknown{"unknown"};
    static const QString String{"string"};
    static const QString Number{"number"};
    static const QString Date{"date"};            // 'MM/DD HH:MM'
    static const QString FullDate{"full_date"};   // Mon Aug 22 02:25:09 2016
}

struct LOADLEVELER_MONITOR_EXPORT QueryCategory
{
public:
    static const QString VALID_ID;

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
    {"id",              "Id",               "Id",           QueryValueType::String,    ""              },// cma20n04.2681148.0
    {"submitted",       "Submitted",        "Submitted",    QueryValueType::Date,      "",             },// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {"class",           "Class",            "Class",        QueryValueType::String,    "%c",           },// normal|operation
    {"dispatch_date",   "Dispatch Date",    "Disp. Date",   QueryValueType::Date,      "%dd",          },// 08/20 12:37
    {"queue_date",      "Queue Date",       "Queue Date",   QueryValueType::Date,      "%dq",          },// 08/20 12:37
    {"unix_group",      "UNIX Group",       "Unix Group",   QueryValueType::String,    "%gu",          },// eps
    {"host_name",       "Running On",       "Running On",   QueryValueType::String,    "%h",           },// cma19n06
    {"step_id",         "Step Id",          "Step Id",      QueryValueType::String,    "%id",          },// cma20n04.2681148.0
    {"image_size",      "Virtual Image Size""Im.Size",      QueryValueType::Number,    "%is",          },// 13
    {"job_name",        "Job Name",         "Job Name",     QueryValueType::String,    "%jn",          },// cma20n04.2681148
    {"job_type",        "Job Type",         "Type",         QueryValueType::String,    "%jt",          },// SER|PAR
    {"host_count",      "Number of Hosts",  "NM",           QueryValueType::Number,    "%nh",          },// 16
    {"owner",           "Job Owner",        "Owner",        QueryValueType::String,    "%o",           },// nwp_qu
    {"priority",        "User Priority",    "PRI",          QueryValueType::Number,    "%p",           },// 50
    {"step_name",       "Step Name",        "Step Name",    QueryValueType::String,    "%sn",          },// 0
    {"status",          "Status",           "ST",           QueryValueType::String,    "%st",          },// R

    // additional categories not used in command argument.
    {"no",              "No.",              "No.",          QueryValueType::Number,    "",             }    // row number in result records
};


static const QVector<QStringList> kLlqDetailQuerySerialJobCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      QueryValueType::String},
    {"owner",           "Owner",            "Owner",            QueryValueType::String},
    {"queue_full_date", "Queue Date",       "Queue Date",       QueryValueType::FullDate},
    {"status",          "Status",           "Status",           QueryValueType::String},
    {"class",           "Class",            "Class",            QueryValueType::String},
    //{"step_type",       "Step Type",        "Step Type",        QueryValueType::String},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Cmd",              QueryValueType::String}
};

static const QVector<QStringList> kLlqDetailQueryParallelCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      QueryValueType::String},
    {"owner",           "Owner",            "Owner",            QueryValueType::String},
    {"queue_full_date", "Queue Date",       "Queue Date",       QueryValueType::FullDate},
    {"status",          "Status",           "Status",           QueryValueType::String},
    {"class",           "Class",            "Class",            QueryValueType::String},
    //{"step_type",       "Step Type",        "Step Type",        QueryValueType::String},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Executable",       QueryValueType::String},
    {"num_task_inst",   "Num Task Inst",    "Num Task Inst",    QueryValueType::Number},
};


}

}
