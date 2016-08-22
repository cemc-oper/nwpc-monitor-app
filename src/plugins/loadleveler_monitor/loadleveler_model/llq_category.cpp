#include "llq_category.h"

using namespace LoadLevelerMonitor::LoadLevelerModel;

const QString LlqQueryCategory::VALID_ID{".valid_id"};

LlqQueryCategory::LlqQueryCategory():
    id_{VALID_ID},
    token_length_{-1}
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
    Q_ASSERT(record.length() == 5);
    QString id = record[0];
    QString display_name = record[1];
    QString comand_line = record[2];
    QString result_title = record[3];
    QString result_type = record[4];
    LlqQueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.command_line_ = comand_line;
    category.result_title_ = result_title;
    category.result_type_ = result_type;
    return category;
}

const QString LlqDetailQueryCategory::VALID_ID{".valid_id"};

LlqDetailQueryCategory::LlqDetailQueryCategory():
    id_{VALID_ID}
{

}

bool LlqDetailQueryCategory::isValid()
{
    return id_ != VALID_ID;
}

bool LlqDetailQueryCategory::operator ==(const LlqDetailQueryCategory &other)
{
    return id_ == other.id_
        && display_name_ == other.display_name_
        && result_label_ == other.result_label_
        && result_type_ == other.result_type_;
}

LlqDetailQueryCategory LlqDetailQueryCategory::createFromStringList(QStringList record)
{
    Q_ASSERT(record.length() == 4);
    QString id = record[0];
    QString display_name = record[1];
    QString result_label = record[2];
    QString result_type = record[3];
    LlqDetailQueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.result_label_ = result_label;
    category.result_type_ = result_type;
    return category;
}
