#pragma once

#include "query_category.h"
#include "query_category_list.h"

#include <QHash>
#include <QMultiMap>
#include <QSet>
#include <QObject>

namespace LoadLevelerMonitor{

namespace Chart{
class ProcessorCondition;
class ModelProcessor;
}

namespace Model{

class LlclassCommandManager;
class QueryModel;

class LlclassCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlclassCommandManagerPrivate(LlclassCommandManager *parent = 0);
    ~LlclassCommandManagerPrivate();

    void initCategoryList();

    QueryCategory findDefaultQueryCategory(const QString &label);
    QueryCategory findDetailQueryCategory(const QString &label) const;

    QueryModel *buildQueryModelFromResponse(const QString &response_str);
    QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_json_document);

    void initModelProcessor();

    QSet<Chart::ModelProcessor*> &processorList(){
        return processor_list_;
    }

    QSet<Chart::ProcessorCondition*> &processorConditionList(){
        return processor_condition_list_;
    }

    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> &processorMap(){
        return processor_map_;
    }

signals:

public slots:

private:
    void registerProcessorMap(Chart::ProcessorCondition* condition, Chart::ModelProcessor* processor);

    LlclassCommandManager *p;

    QueryCategoryList default_query_category_list_;
    QueryCategoryList detail_query_category_list_;

    QSet<Chart::ModelProcessor*> processor_list_;
    QSet<Chart::ProcessorCondition*> processor_condition_list_;
    QMultiMap<Chart::ProcessorCondition*, Chart::ModelProcessor*> processor_map_;

    friend class LlclassCommandManager;
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

}

}
