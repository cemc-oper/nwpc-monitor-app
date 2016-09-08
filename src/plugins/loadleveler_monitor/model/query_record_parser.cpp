#include "query_record_parser.h"

using namespace LoadLevelerMonitor::Model;

QString QueryRecordParser::parse(const QString &)
{
    return QString();
}

QString QueryRecordParser::parse(const QStringList &)
{
    return QString();
}

QStringList QueryRecordParser::parseToList(const QStringList &)
{
    return QStringList();
}

QueryTableRecordParser::QueryTableRecordParser(int begin_pos, int end_pos):
    QueryRecordParser{},
    begin_pos_{begin_pos},
    end_pos_{end_pos}
{

}

QueryTableRecordParser::~QueryTableRecordParser()
{

}

void QueryTableRecordParser::setArguments(int begin_pos, int end_pos)
{
    begin_pos_ = begin_pos;
    end_pos_ = end_pos;
}

QString QueryTableRecordParser::parse(const QString &line)
{
    return line.mid(begin_pos_, end_pos_ - begin_pos_).trimmed();
}

DetailLabelParser::DetailLabelParser(const QString &label):
    QueryRecordParser{},
    label_{label}
{

}

DetailLabelParser::~DetailLabelParser()
{

}

void DetailLabelParser::setArguments(const QString &label)
{
    label_ = label;
}

QString DetailLabelParser::parse(const QStringList &lines)
{
    foreach(QString line, lines)
    {
        int index = line.indexOf(": ");
        if (index == -1)
            continue;

        QString label = line.left(index).trimmed();
        if(label != label_)
            continue;

        // value got
        QString value = line.mid(index + 2).trimmed();

        return value;
    }
    return QString();
}


