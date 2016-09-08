#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QStringList>
#include <QVariantList>

namespace LoadLevelerMonitor{

namespace Model{

class LOADLEVELER_MONITOR_EXPORT QueryRecordParser
{
public:
    QueryRecordParser(){}
    virtual ~QueryRecordParser(){}

    virtual QString parse(const QString &line);
    virtual QString parse(const QStringList &lines);

    virtual QStringList parseToList(const QStringList &lines);
};

// factory
const QString kQueryTableRecordParser = "QueryTableRecordParser";
const QString kDetailLabelParser      = "DetailLabelParser";

class LOADLEVELER_MONITOR_EXPORT QueryRecordParserFactory
{
public:
    QueryRecordParserFactory(){}
    ~QueryRecordParserFactory(){}

    static QueryRecordParser *make(const QString &parser_name, const QVariantList &args);
};


// parser classes

class LOADLEVELER_MONITOR_EXPORT QueryTableRecordParser : public QueryRecordParser
{
public:
    QueryTableRecordParser(int begin_pos, int end_pos);
    ~QueryTableRecordParser();

    void setArguments(int begin_pos, int end_pos);

    QString parse(const QString &line) override;

private:
    int begin_pos_;
    int end_pos_;
};

class LOADLEVELER_MONITOR_EXPORT DetailLabelParser : public QueryRecordParser
{
public:
    DetailLabelParser(const QString &label);
    ~DetailLabelParser();

    void setArguments(const QString &label);

    QString parse(const QStringList& lines) override;

private:
    QString label_;
};

}

}
