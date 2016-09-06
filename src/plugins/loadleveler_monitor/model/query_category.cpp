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

QueryCategory QueryCategory::createLlqDefaultQueryCategory(const tuple<QString, QString, QString, QueryValueType, QString> &record)
{
    QString id = get<0>(record);
    QString display_name = get<1>(record);
    QString label= get<2>(record);
    QueryValueType type = get<3>(record);
    QString comand_line = get<4>(record);
    QueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.label_ = label;
    category.value_type_ = type;
    category.command_line_ = comand_line;
    category.category_type_ = QueryType::LlqDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlqDetialQueryCategory(const tuple<QString, QString, QString, QueryValueType> &record)
{
    QString id = get<0>(record);
    QString display_name = get<1>(record);
    QString label= get<2>(record);
    QueryValueType type = get<3>(record);
    QueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.label_ = label;
    category.value_type_ = type;
    category.category_type_ = QueryType::LlqDetailQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDefaultCategory(const tuple<QString, QString, QString, QueryValueType> &record)
{
    QString id = get<0>(record);
    QString display_name = get<0>(record);
    QString label= get<2>(record);
    QueryValueType type = get<3>(record);
    QueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.label_ = label;
    category.value_type_ = type;
    category.category_type_ = QueryType::LlclassDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDetailCategory(const tuple<QString, QString, QString, QueryValueType> &record)
{
    QString id = get<0>(record);
    QString display_name = get<0>(record);
    QString label= get<2>(record);
    QueryValueType type = get<3>(record);
    QueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.label_ = label;
    category.value_type_ = type;
    category.category_type_ = QueryType::LlclassDetailQuery;
    return category;
}
