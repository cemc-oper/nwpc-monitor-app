#include "llq_command_manager_private.h"

#include "llq_command_manager.h"

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
