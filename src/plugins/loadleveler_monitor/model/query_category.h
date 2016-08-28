#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QVector>
#include <QStringList>

namespace LoadLevelerMonitor{

namespace Model{

enum class QueryType{
    UnknownQuery,
    LlqDefaultQuery,
    LlqDetailQuery,
    LlclassDefaultQuery,
    LlclassDetailQuery
};

namespace QueryValueType{
    static const QString Unknown    {"unknown"};
    static const QString String     {"string"};
    static const QString Number     {"number"};
    static const QString Date       {"date"};            // 'MM/DD HH:MM'
    static const QString FullDate   {"full_date"};   // Mon Aug 22 02:25:09 2016
}

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

    static QueryCategory createLlqCategoryFromStringList(const QStringList &record);
    static QueryCategory createLlclassDefaultCategory(const QStringList &record);
    static QueryCategory createLlclassDetailCategory(const QStringList &record);

    static QueryCategory createCategoryFromStringList(const QStringList &record);

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
    // id,              display_name_,          label,          type                        command_line_,

    // used in default llq output
    {"llq.id",              "Id",                   "Id",           QueryValueType::String,     ""              },// cma20n04.2681148.0
    {"llq.submitted",       "Submitted",            "Submitted",    QueryValueType::Date,       "",             },// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {"llq.class",           "Class",                "Class",        QueryValueType::String,     "%c",           },// normal|operation
    {"llq.dispatch_date",   "Dispatch Date",        "Disp. Date",   QueryValueType::Date,       "%dd",          },// 08/20 12:37
    {"llq.queue_date",      "Queue Date",           "Queue Date",   QueryValueType::Date,       "%dq",          },// 08/20 12:37
    {"llq.unix_group",      "UNIX Group",           "Unix Group",   QueryValueType::String,     "%gu",          },// eps
    {"llq.host_name",       "Running On",           "Running On",   QueryValueType::String,     "%h",           },// cma19n06
    {"llq.step_id",         "Step Id",              "Step Id",      QueryValueType::String,     "%id",          },// cma20n04.2681148.0
    {"llq.image_size",      "Virtual Image Size",   "Im.Size",      QueryValueType::Number,     "%is",          },// 13
    {"llq.job_name",        "Job Name",             "Job Name",     QueryValueType::String,     "%jn",          },// cma20n04.2681148
    {"llq.job_type",        "Job Type",             "Type",         QueryValueType::String,     "%jt",          },// SER|PAR
    {"llq.host_count",      "Number of Hosts",      "NM",           QueryValueType::Number,     "%nh",          },// 16
    {"llq.owner",           "Job Owner",            "Owner",        QueryValueType::String,     "%o",           },// nwp_qu
    {"llq.priority",        "User Priority",        "PRI",          QueryValueType::Number,     "%p",           },// 50
    {"llq.step_name",       "Step Name",            "Step Name",    QueryValueType::String,     "%sn",          },// 0
    {"llq.status",          "Status",               "ST",           QueryValueType::String,     "%st",          },// R

    // additional categories not used in command argument.
    {"llq.no",              "No.",                  "No.",          QueryValueType::Number,     "",             }    // row number in result records
};


static const QVector<QStringList> kLlqDetailQuerySerialJobCategoryList = {
    //id,               display name,       label,              type
    {"llq.id",              "Id",               "Job Step Id",      QueryValueType::String      },
    {"llq.owner",           "Owner",            "Owner",            QueryValueType::String      },
    {"llq.class",           "Class",            "Class",            QueryValueType::String      },
    {"llq.job_script",      "Job Script",       "Cmd",              QueryValueType::String      },
    {"llq.full_status",     "Status",           "Status",           QueryValueType::String      },
    {"llq.queue_full_date", "Queue Date",       "Queue Date",       QueryValueType::FullDate    },
  //{"llq.step_type",       "Step Type",        "Step Type",        QueryValueType::String      },       // Serial | General Parallel

    // additional categories not used in command argument.
    //{"llq.no",              "No.",                  "No.",          QueryValueType::Number,     }    // row number in result records
};

static const QVector<QStringList> kLlqDetailQueryParallelCategoryList = {
    //id,               display name,       label,              type
    {"llq.id",              "Id",               "Job Step Id",      QueryValueType::String      },
    {"llq.owner",           "Owner",            "Owner",            QueryValueType::String      },
    {"llq.class",           "Class",            "Class",            QueryValueType::String      },
    {"llq.job_script",      "Job Script",       "Executable",       QueryValueType::String      },
    {"llq.full_status",     "Status",           "Status",           QueryValueType::String      },
    {"llq.queue_full_date", "Queue Date",       "Queue Date",       QueryValueType::FullDate    },
  //{"llq.step_type",       "Step Type",        "Step Type",        QueryValueType::String      },       // Serial | General Parallel

    // additional categories not used in command argument.
    //{"llq.no",              "No.",                  "No.",          QueryValueType::Number,     }    // row number in result records
};

static const QVector<QStringList> kLlclassDefaultQueryCategoryList = {
    {"llclass.name",            "Name",             "Name",                 QueryValueType::String      },
    {"llclass.max_job_cpu",     "Max Job Cpu",      "MaxJobCPUd+hh:mm:ss",  QueryValueType::String      },
    {"llclass.max_proc_cpu",    "Max Proc Cpu",     "MaxProcCPUd+hh:mm:ss", QueryValueType::String      },
    {"llclass.free_slots",      "Free Slots",       "FreeSlots",            QueryValueType::String      },
    {"llclass.max_slots",       "Max Slots",        "MaxSlots",             QueryValueType::String      },
    {"llclass.description",     "Description",      "Description",          QueryValueType::String      },

    // additional categories not used in command argument.
    {"llclass.no",              "No.",                  "No.",          QueryValueType::Number,     }    // row number in result records
};

static const QVector<QStringList> kLlclassDetailQueryCategoryList = {
    {"llclass.name",                "Name",             "Name",                 QueryValueType::String      },
    {"llclass.exclude_users",       "Exclude Users",    "Exclude_Users",        QueryValueType::String      },
    {"llclass.include_users",       "Include Users",    "Include_Users",        QueryValueType::String      },
    {"llclass.wall_clock_limit",    "Wall clock limit", "Wall_clock_limit",     QueryValueType::String      },
    {"llclass.free_slots",          "Free Slots",       "Free_slots",           QueryValueType::String      },
    {"llclass.max_slots",           "Max Slots",        "Maximum_slots",        QueryValueType::String      },

    // additional categories not used in command argument.
    //{"llclass.no",              "No.",                  "No.",          QueryValueType::Number,     }    // row number in result records
};


}

}
