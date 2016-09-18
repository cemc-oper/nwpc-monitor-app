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

namespace LoadLevelerMonitor{

namespace Model{

enum class QueryType{
    UnknownQuery,
    LlqDefaultQuery,
    LlqDetailQuery,
    LlclassDefaultQuery,
    LlclassDetailQuery
};

LOADLEVELER_MONITOR_EXPORT QVector<int> getCategoryColumnWidth(const QString &mark_line);

struct LOADLEVELER_MONITOR_EXPORT QueryCategory
{
public:
    static const QString kValidId;

    QueryCategory();
    QueryCategory(const QueryCategory &other);

    QueryCategory &operator=(const QueryCategory &other);

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

    // saver: value => item
    QSharedPointer<QueryItemValueSaver> value_saver_; // use QueryValueType to make from factory

    // llq query
    QString command_line_; // %id

};

// id, display_name_, label, type, command_line_, parser_name, parser_arguments
using DefaultQueryCategoryType =
    std::tuple<QString, QString, QString, QueryValueType, QString, QString, QVariantList>;

class LOADLEVELER_MONITOR_EXPORT QueryCategoryFactory
{
public:
    static QueryCategory createLlqDefaultQueryCategory();
    static QueryCategory createLlqDefaultQueryCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlqDetialQueryCategory();
    static QueryCategory createLlqDetialQueryCategory(const DefaultQueryCategoryType &record);

    static QueryCategory createLlclassDefaultCategory();
    static QueryCategory createLlclassDefaultCategory(const DefaultQueryCategoryType &record);
    static QueryCategory createLlclassDetailCategory();
    static QueryCategory createLlclassDetailCategory(const DefaultQueryCategoryType &record);

    static QueryCategory createCateogry(const DefaultQueryCategoryType &record);
    static QueryCategory createDefaultQueryCategory();
    static QueryCategory createDetialQueryCategory();
};

}

}
