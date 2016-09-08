#include "query_category.h"

using namespace LoadLevelerMonitor::Model;
using namespace std;

namespace LoadLevelerMonitor{

namespace Model {
LOADLEVELER_MONITOR_EXPORT QDebug operator <<(QDebug debug, const QueryValueType &value_type)
{
    switch(value_type)
    {
    case QueryValueType::Unknown:
        debug<<"Unknown";
        break;
    case QueryValueType::String:
        debug<<"String";
        break;
    case QueryValueType::Number:
        debug<<"Number";
        break;
    case QueryValueType::Date:
        debug<<"Date";
        break;
    case QueryValueType::FullDate:
        debug<<"FullDate";
        break;
    default:
        Q_ASSERT(0);
        debug<<"unspported";
    }

    return debug;
}

LOADLEVELER_MONITOR_EXPORT QVector<int> getCategoryColumnWidth(const QString &mark_line)
{
    QStringList category_marks = mark_line.split(' ');
    QVector<int> category_column_width(category_marks.size());
    transform(category_marks.begin(), category_marks.end(),
                   category_column_width.begin(), [=](QString str){
        return str.length();
    });
    return category_column_width;
}

}
}


const QString QueryCategory::kValidId{".valid_id"};

bool QueryCategory::isValid()
{
    return id_ != kValidId;
}

bool QueryCategory::operator ==(const QueryCategory &other)
{
    return id_ == other.id_;
}

QueryCategory QueryCategory::createLlqDefaultQueryCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlqDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlqDetialQueryCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlqDetailQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDefaultCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlclassDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDetailCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlclassDetailQuery;
    return category;
}

QueryCategory QueryCategory::createCateogry(const DefaultQueryCategoryType &record)
{
    QString id = get<0>(record);
    QString display_name = get<1>(record);
    QString label= get<2>(record);
    auto type = get<3>(record);
    QString comand_line = get<4>(record);
    QueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.label_ = label;
    category.value_saver_ = QueryItemValueSaverFactory::make(type);
    category.command_line_ = comand_line;
    return category;
}


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
    std::make_tuple(Constant::Llq::Status,         "Status",                   "ST",           QueryValueType::String,      "%st",  kQueryTableRecordParser,    QVariantList{}  ),// R

    // additional categories not used in command argument.
    std::make_tuple(Constant::Llq::No,             "No.",                      "No.",          QueryValueType::Number,      "",     kQueryTableRecordParser,    QVariantList{}  ),    // row number in result records
};

const std::vector<DefaultQueryCategoryType> kLlqDetailQuerySerialJobCategoryList = {
    //              id,                                 display name,           label,              type
    std::make_tuple(Constant::Llq::Id,                  "Id",                   "Job Step Id",      QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Job Step Id"}   ),
    std::make_tuple(Constant::Llq::Owner,               "Owner",                "Owner",            QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Owner"}   ),
    std::make_tuple(Constant::Llq::Class,               "Class",                "Class",            QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Class"}   ),
    std::make_tuple(Constant::Llq::JobScript,           "Job Script",           "Cmd",              QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Cmd"}   ),
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Status"}   ),
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
    std::make_tuple(Constant::Llq::FullStatus,          "Status",               "Status",           QueryValueType::String,     "",     kDetailLabelParser,    QVariantList{"Status"}   ),
    std::make_tuple(Constant::Llq::QueueFullDate,       "Queue Date",           "Queue Date",       QueryValueType::FullDate,   "",     kDetailLabelParser,    QVariantList{"Queue Date"}   ),
    std::make_tuple(Constant::Llq::NodeMinimum,         "Node Minimun",         "Node minimum",     QueryValueType::Number,     "",     kDetailLabelParser,    QVariantList{"Node minimum"}   ),
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
