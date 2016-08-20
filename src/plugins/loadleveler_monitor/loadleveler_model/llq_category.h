#pragma once

#include <QString>
#include <QVector>
#include <QStringList>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

const QString TYPE_STRING{"string"};
const QString TYPE_NUMBER{"number"};
const QString TYPE_DATE{"date"};    // 'MM/DD HH:MM'

struct LlqCategory
{
public:
    static const QString VALID_ID;

    LlqCategory();
    bool isValid();
    bool operator ==(const LlqCategory &other);

    static LlqCategory createFromStringList(QStringList record);

    QString id_;
    QString display_name_; // step id
    QString command_line_; // %id
    QString result_title_; // Step Id
    QString result_type_; // string or number
};

static const QVector<QStringList> LLQ_CATEGARY_LIST = {
    // id,              display_name_,      command_line_,  result_title_,  result_type
    {"class",           "Class",            "%c",           "Class",        TYPE_STRING},   // normal|operation
    {"dispatch_date",   "Dispatch Date",    "%dd",          "Disp. Date",   TYPE_DATE},     // 08/20 12:37
    {"queue_date",      "Queue Date",       "%dq",          "Queue Date",   TYPE_DATE},     // 08/20 12:37
    {"unix_group",      "UNIX Group",       "%gu",          "Unix Group",   TYPE_STRING},   // eps
    {"host_name",       "Host Name",        "%h",           "Running On",   TYPE_STRING},   // cma19n06
    {"step_id",         "Step Id",          "%id",          "Step Id",      TYPE_STRING},   // cma20n04.2681148.0
    {"image_size",      "Virtual Image Size",   "%is",      "Im.Size",      TYPE_NUMBER},   // 13
    {"job_name",        "Job Name",         "%jn",          "Job Name",     TYPE_STRING},   // cma20n04.2681148
    {"job_type",        "Job Type",         "%jt",          "Type",         TYPE_STRING},   // SER|PAR
    {"host_count",      "Number of Hosts",  "%nh",          "NM",           TYPE_NUMBER},   // 16
    {"owner",           "Job Owner",        "%o",           "Owner",        TYPE_STRING},   // nwp_qu
    {"priority",        "User Priority",    "%p",           "PRI",          TYPE_NUMBER},   // 50
    {"step_name",       "Step Name",        "%sn",          "Step Name",    TYPE_STRING},   // 0
    {"status",          "Status",           "%st",          "ST",           TYPE_STRING}    // R
};

}

}
