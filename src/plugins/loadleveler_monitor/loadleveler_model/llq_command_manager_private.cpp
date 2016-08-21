#include "llq_command_manager_private.h"

#include "llq_command_manager.h"
#include "job_query_item.h"
#include "job_query_model.h"

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QtDebug>

#include <algorithm>

using namespace LoadLevelerMonitor::LoadLevelerModel;

LlqCommandManagerPrivate::LlqCommandManagerPrivate(LlqCommandManager *parent) :
    QObject{parent},
    p{parent}
{

}

void LlqCommandManagerPrivate::initLlqCategoryList()
{
    llq_category_list_.clear();
    foreach(QStringList record, LLQ_CATEGARY_LIST)
    {
        llq_category_list_.append(LlqCategory::createFromStringList(record));
    }
}

QVector<LlqCategory> LlqCommandManagerPrivate::llqCategoryList()
{
    return llq_category_list_;
}

LlqCategory LlqCommandManagerPrivate::findCategory(const QString result_title)
{
    LlqCategory result_category;
    for(int i=0; i<llq_category_list_.length(); i++)
    {
        LlqCategory category = llq_category_list_[i];
        if( category.result_title_ == result_title )
        {
            result_category = category;
            break;
        }
    }
    return result_category;
}

JobQueryModel *LlqCommandManagerPrivate::buildLlqQueryModelFromResponse(const QString &response_str)
{
    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] begin";

    QJsonDocument doc = QJsonDocument::fromJson(response_str.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] result is not a json string.";
        return nullptr;
    }

    QJsonObject result_object = doc.object();

    if( result_object.contains("error"))
    {
        QString error_message = result_object["data"].toObject()["message"].toObject()["error_message"].toString();
        qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] ERROR:"<<error_message;
        return nullptr;
    }

    QString app = result_object["app"].toString();
    QString type = result_object["type"].toString();
    QJsonObject data = result_object["data"].toObject();

    QJsonObject request = data["request"].toObject();
    QString command = request["command"].toString();
    QJsonArray arguments = request["arguments"].toArray();
    QStringList arg_list;
    foreach(QJsonValue an_argument, arguments)
    {
        arg_list.append(an_argument.toString());
    }

    QJsonObject message = data["response"].toObject()["message"].toObject();
    QString output_message = message["output"].toString();

    //qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse]"<<output_message;

    JobQueryModel *model = buildLlqQueryModel(output_message);


    qDebug()<<"[LlqCommandManagerPrivate::buildLlqQueryModelFromResponse] end";
    return model;
}

JobQueryModel *LlqCommandManagerPrivate::buildLlqQueryModel(const QString &output)
{
    Q_ASSERT(!output.isEmpty());

    QStringList lines = output.split('\n');

    // 不能直接对每行使用trimmed，因为第一项和最后一项都可能为空，trimmed将破坏数据。
//    std::transform(lines.begin(), lines.end(),
//                   lines.begin(), [=](QString str){
//        return str.trimmed();
//    });

    return JobQueryModel::buildFromLlqResponseLines(lines);
}
