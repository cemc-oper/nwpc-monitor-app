#include "query_category.h"

using namespace LoadLevelerMonitor::LoadLevelerModel;

const QString QueryCategory::VALID_ID{".valid_id"};

QueryCategory::QueryCategory():
    id_{VALID_ID},
    token_length_{-1},
    category_type_{QueryType::UnknownQuery}
{

}

bool QueryCategory::isValid()
{
    return id_ != VALID_ID;
}

bool QueryCategory::operator ==(const QueryCategory &other)
{
    return id_ == other.id_;
}

QueryCategory QueryCategory::createFromStringList(QStringList record)
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
        category.category_type_ = QueryType::LlqDefaultQuery;
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
        category.category_type_ = QueryType::LlqDetailQuery;
        return category;
    }
    else
    {
        return QueryCategory();
    }
}
