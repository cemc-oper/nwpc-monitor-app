#include "llq_category.h"

using namespace LoadLevelerMonitor::LoadLevelerModel;

const QString LlqCategory::VALID_ID{".valid_id"};

LlqCategory::LlqCategory():
    id_{VALID_ID}
{

}

bool LlqCategory::isValid()
{
    return id_ != VALID_ID;
}

bool LlqCategory::operator ==(const LlqCategory &other)
{
    return id_ == other.id_;
}

LlqCategory LlqCategory::createFromStringList(QStringList record)
{
    Q_ASSERT(record.length() == 5);
    QString id = record[0];
    QString display_name = record[1];
    QString comand_line = record[2];
    QString result_title = record[3];
    QString result_type = record[4];
    LlqCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.command_line_ = comand_line;
    category.result_title_ = result_title;
    category.result_type_ = result_type;
    return category;
}
