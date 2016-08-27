#include "query_category.h"

using namespace LoadLevelerMonitor::Model;

const QString QueryCategory::kValidId{".valid_id"};

bool QueryCategory::isValid()
{
    return id_ != kValidId;
}

bool QueryCategory::operator ==(const QueryCategory &other)
{
    return id_ == other.id_;
}

QueryCategory QueryCategory::createLlqCategoryFromStringList(const QStringList &record)
{
    QueryCategory category = QueryCategory::createCategoryFromStringList(record);
    if(record.length() == 5)
    {
        category.category_type_ = QueryType::LlqDefaultQuery;
    }
    else if(record.length()==4)
    {
        category.category_type_ = QueryType::LlqDetailQuery;
    }
    return category;
}

QueryCategory QueryCategory::createLlclassDefaultCategory(const QStringList &record)
{
    QueryCategory category = QueryCategory::createCategoryFromStringList(record);
    category.category_type_ = QueryType::LlclassDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDetailCategory(const QStringList &record)
{
    QueryCategory category = QueryCategory::createCategoryFromStringList(record);
    category.category_type_ = QueryType::LlclassDetailQuery;
    return category;
}

QueryCategory QueryCategory::createCategoryFromStringList(const QStringList &record)
{
    if(record.length() == 5)
    {
        QString id = record[0];
        QString display_name = record[1];
        QString label= record[2];
        QString type = record[3];
        QString comand_line = record[4];
        QueryCategory category;
        category.id_ = id;
        category.display_name_ = display_name;
        category.label_ = label;
        category.value_type_ = type;
        category.command_line_ = comand_line;
        return category;
    }
    else if(record.length()==4)
    {
        QString id = record[0];
        QString display_name = record[1];
        QString label = record[2];
        QString type = record[3];
        QueryCategory category;
        category.id_ = id;
        category.display_name_ = display_name;
        category.label_ = label;
        category.value_type_ = type;
        return category;
    }
    else
    {
        return QueryCategory();
    }
}
