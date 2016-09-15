#include "query_category.h"

using namespace LoadLevelerMonitor::Model;
using namespace std;

namespace LoadLevelerMonitor{

namespace Model {

/*
llq 和 llclass 的输出格式如下：
Id                       Owner      Submitted   ST PRI Class        Running On
------------------------ ---------- ----------- -- --- ------------ -----------
cma20n02.2942180.0       nwp_pd      9/14 04:01 R  100 serial_op    cma18n04
cma20n01.2957161.0       nwp_vfy     9/15 10:00 R  100 serial       cma20n06

其中第二行
------------------------ ---------- ----------- -- --- ------------ -----------
就是标志行，可以得到每列的起止字符数。
本函数返回每段-*的长度。
 */
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

QueryCategory::QueryCategory():
    id_                 {kValidId},
    display_name_       {""},
    label_              {""},
    record_parser_      {new QueryRecordParser},
    value_saver_        {new QueryItemValueSaver},
    category_type_      {QueryType::UnknownQuery},
    command_line_       {""}
{
}

QueryCategory::QueryCategory(const QueryCategory &other):
    id_                 {other.id_},
    display_name_       {other.display_name_},
    label_              {other.label_},
    value_saver_        {other.value_saver_},
    category_type_      {other.category_type_},
    command_line_       {other.command_line_}
{
    QVariantList args;
    foreach(QVariant arg, other.record_parser_->arguments())
    {
        args.append(arg);
    }
    record_parser_.reset(QueryRecordParserFactory::make(other.record_parser_->type(), args));
}

QueryCategory &QueryCategory::operator=(const QueryCategory &other)
{
    id_                 = other.id_;
    display_name_       = other.display_name_;
    label_              = other.label_;
    value_saver_        = other.value_saver_;
    category_type_      = other.category_type_;

    QVariantList args;
    foreach(QVariant arg, other.record_parser_->arguments())
    {
        args.append(arg);
    }
    record_parser_.reset(QueryRecordParserFactory::make(other.record_parser_->type(), args));
    command_line_       = other.command_line_;
    return *this;
}

bool QueryCategory::isValid()
{
    return id_ != kValidId;
}

bool QueryCategory::operator ==(const QueryCategory &other)
{
    return id_ == other.id_;
}

QueryCategory QueryCategory::createLlqDefaultQueryCategory()
{
    QueryCategory category = createDefaultQueryCategory();
    category.category_type_ = QueryType::LlqDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlqDefaultQueryCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlqDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlqDetialQueryCategory()
{
    QueryCategory category = createDetialQueryCategory();
    category.category_type_ = QueryType::LlqDetailQuery;
    return category;
}

QueryCategory QueryCategory::createLlqDetialQueryCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlqDetailQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDefaultCategory()
{
    QueryCategory category = createDefaultQueryCategory();
    category.category_type_ = QueryType::LlclassDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDefaultCategory(const DefaultQueryCategoryType &record)
{
    QueryCategory category = createCateogry(record);
    category.category_type_ = QueryType::LlclassDefaultQuery;
    return category;
}

QueryCategory QueryCategory::createLlclassDetailCategory()
{
    QueryCategory category = createDetialQueryCategory();
    category.category_type_ = QueryType::LlclassDetailQuery;
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
    QString record_parser_type = get<5>(record);
    QVariantList record_parser_agrs = get<6>(record);
    QueryCategory category;
    category.id_ = id;
    category.display_name_ = display_name;
    category.label_ = label;
    category.record_parser_.reset(QueryRecordParserFactory::make(
                                      record_parser_type,
                                      record_parser_agrs));
    category.value_saver_ = QueryItemValueSaverFactory::make(type);
    category.command_line_ = comand_line;
    return category;
}

QueryCategory QueryCategory::createDefaultQueryCategory()
{
    QueryCategory category;
    category.record_parser_.reset(
                QueryRecordParserFactory::make(kQueryTableRecordParser, QVariantList()));
    category.value_saver_ = QueryItemValueSaverFactory::make(QueryValueType::Unknown);
    return category;
}

QueryCategory QueryCategory::createDetialQueryCategory()
{
    QueryCategory category;
    category.record_parser_.reset(
                QueryRecordParserFactory::make(kQueryTableRecordParser, QVariantList()));
    category.value_saver_ = QueryItemValueSaverFactory::make(QueryValueType::Unknown);
    return category;
}
