#include "query_record_parser.h"

#include <exception>

using namespace LoadLevelerMonitor::Model;

/*
 * QueryRecordParser
 */

void QueryRecordParser::setArguments(const QVariantList &args)
{

}

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

// factory

QueryRecordParser *QueryRecordParserFactory::make(const QString &parser_name, const QVariantList &args)
{
    QueryRecordParser *parser = nullptr;
    if(parser_name == kQueryTableRecordParser)
    {
        parser = new QueryTableRecordParser{args};
    }
    else if(parser_name == kDetailLabelParser)
    {
        parser = new DetailLabelParser{args};
    }
    else
    {
        throw std::invalid_argument(QString("error parser name: " + parser_name).toStdString());
    }

    return parser;
}


// parsers

/*
 * QueryTableRecordParser
 */


QueryTableRecordParser::QueryTableRecordParser():
    QueryTableRecordParser{QVariantList{}}
{

}

QueryTableRecordParser::QueryTableRecordParser(const QVariantList &args):
    QueryRecordParser{}
{
    if(args.isEmpty())
    {
        begin_pos_ = -1;
        end_pos_ = -1;
        return;
    }
    setArguments(args);
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

void QueryTableRecordParser::setArguments(const QVariantList &args)
{
    if(args.length() != 2)
        throw std::invalid_argument("QueryTableRecordParser need 2 args");

    if(!args[0].canConvert<int>())
        throw std::invalid_argument("QueryTableRecordParser arg 1 must be int");
    int begin_pos = args[0].toInt();

    if(!args[1].canConvert<int>())
        throw std::invalid_argument("QueryTableRecordParser arg 2 must be int");
    int end_pos = args[1].toInt();

    begin_pos_ = begin_pos;
    end_pos_ = end_pos;
}

QString QueryTableRecordParser::parse(const QString &line)
{
    return line.mid(begin_pos_, end_pos_ - begin_pos_).trimmed();
}

/*
 * DetailLabelParser
 */

DetailLabelParser::DetailLabelParser():
    DetailLabelParser{QVariantList{}}
{

}

DetailLabelParser::DetailLabelParser(const QVariantList &args):
    QueryRecordParser{}
{
    if(args.isEmpty())
    {
        label_ = "";
        return;
    }
    setArguments(args);
}


DetailLabelParser::DetailLabelParser(const QString &label):
    QueryRecordParser{},
    label_{label}
{

}

DetailLabelParser::~DetailLabelParser()
{

}

void DetailLabelParser::setArguments(const QVariantList &args)
{
    if(args.length() != 1)
        throw std::invalid_argument("DetailLabelParser need 1 args");

    if(!args[0].canConvert<QString>())
        throw std::invalid_argument("DetailLabelParser arg 1 must be QString");
    QString label = args[0].toString();

    label_ = label;
}

QString DetailLabelParser::parse(const QStringList &lines)
{
    Q_ASSERT(!label_.isEmpty());
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
