#include "llq_category.h"

using namespace LoadLevelerMonitor::LoadLevelerModel;

const QString LlqQueryCategory::VALID_ID{".valid_id"};

LlqQueryCategory::LlqQueryCategory():
    id_{VALID_ID},
    token_length_{-1},
    category_type_{CategoryType::NormalQuery}
{

}

bool LlqQueryCategory::isValid()
{
    return id_ != VALID_ID;
}

bool LlqQueryCategory::operator ==(const LlqQueryCategory &other)
{
    return id_ == other.id_;
}

LlqQueryCategory LlqQueryCategory::createFromStringList(QStringList record)
{
    if(record.length() == 5)
    {
        QString id = record[0];
        QString display_name = record[1];
        QString label= record[2];
        QString type = record[3];
        QString comand_line = record[4];
        LlqQueryCategory category;
        category.id_ = id;
        category.display_name_ = display_name;
        category.label_ = label;
        category.value_type_ = type;
        category.command_line_ = comand_line;
        category.category_type_ = CategoryType::NormalQuery;
        return category;
    }
    else if(record.length()==4)
    {
        QString id = record[0];
        QString display_name = record[1];
        QString label = record[2];
        QString type = record[3];
        LlqQueryCategory category;
        category.id_ = id;
        category.display_name_ = display_name;
        category.label_ = label;
        category.value_type_ = type;
        category.category_type_ = CategoryType::DetailQuery;
        return category;
    }
    else
    {
        return LlqQueryCategory();
    }
}
