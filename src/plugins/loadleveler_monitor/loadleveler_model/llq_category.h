#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QVector>
#include <QStringList>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

const QString TYPE_STRING{"string"};
const QString TYPE_NUMBER{"number"};
const QString TYPE_DATE{"date"};    // 'MM/DD HH:MM'
const QString TYPE_FULL_DATE{"full_date"}; // Mon Aug 22 02:25:09 2016

struct LOADLEVELER_MONITOR_EXPORT LlqQueryCategory
{
public:
    enum class CategoryType{
        NormalQuery,
        DetailQuery
    };

    enum class ValueType {
        Unknown,
        String,
        Number,
        Date,
        FullDate
    };

    static const QString VALID_ID;

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
    {"id",              "Id",               "Id",           TYPE_STRING,    ""              },// cma20n04.2681148.0
    {"submitted",       "Submitted",        "Submitted",    TYPE_DATE,      "",             },// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {"class",           "Class",            "Class",        TYPE_STRING,    "%c",           },// normal|operation
    {"dispatch_date",   "Dispatch Date",    "Disp. Date",   TYPE_DATE,      "%dd",          },// 08/20 12:37
    {"queue_date",      "Queue Date",       "Queue Date",   TYPE_DATE,      "%dq",          },// 08/20 12:37
    {"unix_group",      "UNIX Group",       "Unix Group",   TYPE_STRING,    "%gu",          },// eps
    {"host_name",       "Running On",       "Running On",   TYPE_STRING,    "%h",           },// cma19n06
    {"step_id",         "Step Id",          "Step Id",      TYPE_STRING,    "%id",          },// cma20n04.2681148.0
    {"image_size",      "Virtual Image Size""Im.Size",      TYPE_NUMBER,    "%is",          },// 13
    {"job_name",        "Job Name",         "Job Name",     TYPE_STRING,    "%jn",          },// cma20n04.2681148
    {"job_type",        "Job Type",         "Type",         TYPE_STRING,    "%jt",          },// SER|PAR
    {"host_count",      "Number of Hosts",  "NM",           TYPE_NUMBER,    "%nh",          },// 16
    {"owner",           "Job Owner",        "Owner",        TYPE_STRING,    "%o",           },// nwp_qu
    {"priority",        "User Priority",    "PRI",          TYPE_NUMBER,    "%p",           },// 50
    {"step_name",       "Step Name",        "Step Name",    TYPE_STRING,    "%sn",          },// 0
    {"status",          "Status",           "ST",           TYPE_STRING,    "%st",          },// R

    // additional categories not used in command argument.
    {"no",              "No.",              "No.",          TYPE_NUMBER,    "",             }    // row number in result records
};


static const QVector<QStringList> kLlqDetailQuerySerialJobCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      TYPE_STRING},
    {"owner",           "Owner",            "Owner",            TYPE_STRING},
    {"submitted",       "Submitted",        "Queue Date",       TYPE_FULL_DATE},
    {"status",          "Status",           "Status",           TYPE_STRING},
    {"class",           "Class",            "Class",            TYPE_STRING},
    //{"step_type",       "Step Type",        "Step Type",        TYPE_STRING},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Cmd",              TYPE_STRING}
};

static const QVector<QStringList> kLlqDetailQueryParallelCategoryList = {
    //id,               display name,       label,              type
    {"id",              "Id",               "Job Step Id",      TYPE_STRING},
    {"owner",           "Owner",            "Owner",            TYPE_STRING},
    {"submitted",       "Submitted",        "Queue Date",       TYPE_FULL_DATE},
    {"status",          "Status",           "Status",           TYPE_STRING},
    {"class",           "Class",            "Class",            TYPE_STRING},
    //{"step_type",       "Step Type",        "Step Type",        TYPE_STRING},       // Serial | General Parallel
    {"job_script",      "Job Script",       "Executable",       TYPE_STRING},
    {"num_task_inst",   "Num Task Inst",    "Num Task Inst",    TYPE_NUMBER},
};


}

}
