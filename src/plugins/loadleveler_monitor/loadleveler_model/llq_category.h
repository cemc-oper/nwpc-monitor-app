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
    static const QString VALID_ID;

    LlqQueryCategory();

    bool isValid();
    bool operator ==(const LlqQueryCategory &other);

    static LlqQueryCategory createFromStringList(QStringList record);

    QString id_;
    QString display_name_; // step id
    QString command_line_; // %id
    QString result_title_; // Step Id
    QString result_type_; // string or number,

    int token_length_; // length in output line
};

static const QVector<QStringList> LLQ_QUERY_CATEGARY_LIST = {
    // id,              display_name_,      command_line_,  result_title_,  result_type

    // used in default llq output
    {"id",              "Id",               "",             "Id",           TYPE_STRING},   // cma20n04.2681148.0
    {"submitted",       "Submitted",        "",             "Submitted",    TYPE_DATE},     // same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {"class",           "Class",            "%c",           "Class",        TYPE_STRING},   // normal|operation
    {"dispatch_date",   "Dispatch Date",    "%dd",          "Disp. Date",   TYPE_DATE},     // 08/20 12:37
    {"queue_date",      "Queue Date",       "%dq",          "Queue Date",   TYPE_DATE},     // 08/20 12:37
    {"unix_group",      "UNIX Group",       "%gu",          "Unix Group",   TYPE_STRING},   // eps
    {"host_name",       "Running On",       "%h",           "Running On",   TYPE_STRING},   // cma19n06
    {"step_id",         "Step Id",          "%id",          "Step Id",      TYPE_STRING},   // cma20n04.2681148.0
    {"image_size",      "Virtual Image Size",   "%is",      "Im.Size",      TYPE_NUMBER},   // 13
    {"job_name",        "Job Name",         "%jn",          "Job Name",     TYPE_STRING},   // cma20n04.2681148
    {"job_type",        "Job Type",         "%jt",          "Type",         TYPE_STRING},   // SER|PAR
    {"host_count",      "Number of Hosts",  "%nh",          "NM",           TYPE_NUMBER},   // 16
    {"owner",           "Job Owner",        "%o",           "Owner",        TYPE_STRING},   // nwp_qu
    {"priority",        "User Priority",    "%p",           "PRI",          TYPE_NUMBER},   // 50
    {"step_name",       "Step Name",        "%sn",          "Step Name",    TYPE_STRING},   // 0
    {"status",          "Status",           "%st",          "ST",           TYPE_STRING},   // R

    // additional categories not used in command argument.
    {"no",              "No.",              "",             "No.",             TYPE_NUMBER}    // row number in result records
};


struct LOADLEVELER_MONITOR_EXPORT LlqDetailQueryCategory
{
public:
    static const QString VALID_ID;

    LlqDetailQueryCategory();

    bool isValid();
    bool operator ==(const LlqDetailQueryCategory &other);

    static LlqDetailQueryCategory createFromStringList(QStringList record);

    QString id_;
    QString display_name_;
    QString result_label_;
    QString result_type_;
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
