#pragma once

#include "../loadleveler_monitor_global.h"
#include "model_constants.h"

#include "query_record_parser.h"
#include "query_item_value_saver.h"

#include <QString>
#include <QVector>
#include <QStringList>
#include <QtDebug>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QVariantList>

#include <tuple>
#include <vector>

namespace LoadLevelerMonitor{

namespace Model{

enum class QueryType{
    UnknownQuery,
    LlqDefaultQuery,
    LlqDetailQuery,
    LlclassDefaultQuery,
    LlclassDetailQuery
};

LOADLEVELER_MONITOR_EXPORT QDebug operator <<(QDebug debug, const QueryValueType &value_type);

LOADLEVELER_MONITOR_EXPORT QVector<int> getCategoryColumnWidth(const QString &mark_line);


// id, display_name_, label, type, command_line_, parser_name, parser_arguments
using DefaultQueryCategoryType =
    std::tuple<QString, QString, QString, QueryValueType, QString, QString, QVariantList>;

struct LOADLEVELER_MONITOR_EXPORT QueryCategory
{
public:
    static const QString kValidId;

    QueryCategory():
        id_             {kValidId},
        display_name_   {""},
        label_          {""},
        value_saver_    {new QueryItemValueSaver},
        category_type_  {QueryType::UnknownQuery},
        command_line_   {""},
        token_length_   {-1}
    {
    }
    QueryCategory(const QueryCategory &other):
        id_             {other.id_},
        display_name_   {other.display_name_},
        label_          {other.label_},
        value_saver_    {other.value_saver_},
        category_type_  {other.category_type_},
        command_line_   {other.command_line_},
        token_length_   {other.token_length_}
    {
    }

    QueryCategory& operator=(const QueryCategory &other)
    {
        id_             = other.id_;
        display_name_   = other.display_name_;
        label_          = other.label_;
        value_saver_    = other.value_saver_;
        category_type_  = other.category_type_;
        command_line_   = other.command_line_;
        token_length_   = other.token_length_;
        return *this;
    }

    ~QueryCategory(){}

    virtual bool isValid();
    bool operator ==(const QueryCategory &other);

public:
    QString id_;
    QString display_name_; // step id
    QString label_; // Step Id

    // parser: record => value
    QueryType category_type_;
    QScopedPointer<QueryRecordParser> record_parser_;
    int token_length_; // length in output line

    // saver: value => item
    QSharedPointer<QueryItemValueSaver> value_saver_; // use QueryValueType to make from factory,

    // llq query
    QString command_line_; // %id

public:
    static QueryCategory createLlqDefaultQueryCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlqDetialQueryCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlclassDefaultCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlclassDetailCategory(const DefaultQueryCategoryType &record);

    static QueryCategory createCateogry(const DefaultQueryCategoryType &record);
};

const std::vector<DefaultQueryCategoryType> kLlqDefaultQueryCategoryList;
const std::vector<DefaultQueryCategoryType> kLlqDetailQuerySerialJobCategoryList;
const std::vector<DefaultQueryCategoryType> kLlqDetailQueryParallelCategoryList;
const std::vector<DefaultQueryCategoryType> kLlclassDefaultQueryCategoryList;
const std::vector<DefaultQueryCategoryType> kLlclassDetailQueryCategoryList;

}

}
