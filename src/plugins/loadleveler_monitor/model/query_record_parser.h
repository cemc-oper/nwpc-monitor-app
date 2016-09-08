#pragma once

#include "../loadleveler_monitor_global.h"

#include <QString>
#include <QStringList>

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
