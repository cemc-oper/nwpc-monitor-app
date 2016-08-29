#pragma once

#include "../loadleveler_monitor_global.h"
#include "model_constants.h"

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
    // id,                          display_name_,              label,          type                        command_line_,

    // used in default llq output
    {Constant::Llq::Id,             "Id",                       "Id",           QueryValueType::String,     ""              },// cma20n04.2681148.0
    {Constant::Llq::Submitted,      "Submitted",                "Submitted",    QueryValueType::Date,       "",             },// same as Queue Date, use in standard llq.

    // used in llq's -f arguemnt.
    {Constant::Llq::Class,          "Class",                    "Class",        QueryValueType::String,     "%c",           },// normal|operation
    {Constant::Llq::DispatchDate,   "Dispatch Date",            "Disp. Date",   QueryValueType::Date,       "%dd",          },// 08/20 12:37
    {Constant::Llq::QueueDate,      "Queue Date",               "Queue Date",   QueryValueType::Date,       "%dq",          },// 08/20 12:37
    {Constant::Llq::UnixGroup,      "UNIX Group",               "Unix Group",   QueryValueType::String,     "%gu",          },// eps
    {Constant::Llq::HostName,       "Running On",               "Running On",   QueryValueType::String,     "%h",           },// cma19n06
    {Constant::Llq::StepId,         "Step Id",                  "Step Id",      QueryValueType::String,     "%id",          },// cma20n04.2681148.0
    {Constant::Llq::ImageSize,      "Virtual Image Size",       "Im.Size",      QueryValueType::Number,     "%is",          },// 13
    {Constant::Llq::JobName,        "Job Name",                 "Job Name",     QueryValueType::String,     "%jn",          },// cma20n04.2681148
    {Constant::Llq::JobType,        "Job Type",                 "Type",         QueryValueType::String,     "%jt",          },// SER|PAR
    {Constant::Llq::HostCount,      "Number of Hosts",          "NM",           QueryValueType::Number,     "%nh",          },// 16
    {Constant::Llq::Owner,          "Job Owner",                "Owner",        QueryValueType::String,     "%o",           },// nwp_qu
    {Constant::Llq::Priority,       "User Priority",            "PRI",          QueryValueType::Number,     "%p",           },// 50
    {Constant::Llq::StepName,       "Step Name",                "Step Name",    QueryValueType::String,     "%sn",          },// 0
    {Constant::Llq::Status,         "Status",                   "ST",           QueryValueType::String,     "%st",          },// R

    // additional categories not used in command argument.
    {Constant::Llq::No,             "No.",                      "No.",          QueryValueType::Number,     "",             }    // row number in result records
};


static const QVector<QStringList> kLlqDetailQuerySerialJobCategoryList = {
    //id,                               display name,           label,              type
    {Constant::Llq::Id,                 "Id",                   "Job Step Id",      QueryValueType::String      },
    {Constant::Llq::Owner,              "Owner",                "Owner",            QueryValueType::String      },
    {Constant::Llq::Class,              "Class",                "Class",            QueryValueType::String      },
    {Constant::Llq::JobScript,          "Job Script",           "Cmd",              QueryValueType::String      },
    {Constant::Llq::FullStatus,         "Status",               "Status",           QueryValueType::String      },
    {Constant::Llq::QueueFullDate,      "Queue Date",           "Queue Date",       QueryValueType::FullDate    },
  //{Constant::Llq::StepType,           "Step Type",            "Step Type",        QueryValueType::String      },       // Serial | General Parallel

    // additional categories not used in command argument.
  //{Constant::Llq::No,                 "No.",                  "No.",              QueryValueType::Number,     }    // row number in result records
};

static const QVector<QStringList> kLlqDetailQueryParallelCategoryList = {
    //id,                               display name,           label,              type
    {Constant::Llq::Id,                 "Id",                   "Job Step Id",      QueryValueType::String      },
    {Constant::Llq::Owner,              "Owner",                "Owner",            QueryValueType::String      },
    {Constant::Llq::Class,              "Class",                "Class",            QueryValueType::String      },
    {Constant::Llq::JobScript,          "Job Script",           "Executable",       QueryValueType::String      },
    {Constant::Llq::FullStatus,         "Status",               "Status",           QueryValueType::String      },
    {Constant::Llq::QueueFullDate,      "Queue Date",           "Queue Date",       QueryValueType::FullDate    },
  //{Constant::Llq::StepType,           "Step Type",            "Step Type",        QueryValueType::String      },       // Serial | General Parallel

    // additional categories not used in command argument.
  //{Constant::Llq::No,                 "No.",                  "No.",              QueryValueType::Number,     }    // row number in result records
};

static const QVector<QStringList> kLlclassDefaultQueryCategoryList = {
    {Constant::Llclass::Name,           "Name",                 "Name",                 QueryValueType::String      },
    {Constant::Llclass::MaxJobCpu,      "Max Job Cpu",          "MaxJobCPUd+hh:mm:ss",  QueryValueType::String      },
    {Constant::Llclass::MaxProcCpu,     "Max Proc Cpu",         "MaxProcCPUd+hh:mm:ss", QueryValueType::String      },
    {Constant::Llclass::FreeSlots,      "Free Slots",           "FreeSlots",            QueryValueType::String      },
    {Constant::Llclass::MaxSlots,       "Max Slots",            "MaxSlots",             QueryValueType::String      },
    {Constant::Llclass::Description,    "Description",          "Description",          QueryValueType::String      },

    // additional categories not used in command argument.
    {Constant::Llclass::No,             "No.",                  "No.",                  QueryValueType::Number,     }    // row number in result records
};

static const QVector<QStringList> kLlclassDetailQueryCategoryList = {
    {Constant::Llclass::Name,               "Name",             "Name",                 QueryValueType::String      },
    {Constant::Llclass::ExcludeUsers,       "Exclude Users",    "Exclude_Users",        QueryValueType::String      },
    {Constant::Llclass::IncludeUsers,       "Include Users",    "Include_Users",        QueryValueType::String      },
    {Constant::Llclass::WallColockLimit,    "Wall clock limit", "Wall_clock_limit",     QueryValueType::String      },
    {Constant::Llclass::FreeSlots,          "Free Slots",       "Free_slots",           QueryValueType::String      },
    {Constant::Llclass::MaxSlots,           "Max Slots",        "Maximum_slots",        QueryValueType::String      },

    // additional categories not used in command argument.
  //{Constant::Llclass::No,                 "No.",                  "No.",          QueryValueType::Number,     }    // row number in result records
};


}

}
