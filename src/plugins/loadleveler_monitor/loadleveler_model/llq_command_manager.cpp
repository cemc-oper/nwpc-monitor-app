#include "llq_command_manager.h"
#include "llq_command_manager_private.h"

#include "query_model.h"

using namespace LoadLevelerMonitor::LoadLevelerModel;

static LlqCommandManager *llq_command_manager_instance = nullptr;
static LlqCommandManagerPrivate *d = nullptr;

LlqCommandManager *LlqCommandManager::instance()
{
    return llq_command_manager_instance;
}

void LlqCommandManager::initialize()
{
    d->initLlqCategoryList();
}

QVector<QueryCategory> LlqCommandManager::llqDefaultCategoryList()
{
    return d->llqCategoryList();
}

QVector<QueryCategory> LlqCommandManager::llqSerialJobDetailQueryCategoryList()
{
    return d->llq_serial_job_detail_category_list_;
}

QVector<QueryCategory> LlqCommandManager::llqParellelJobDetailQueryCategoryList()
{
    return d->llq_parallel_job_detail_category_list_;
}

QueryCategory LlqCommandManager::findLlqDefaultQueryCategory(const QString result_title)
{
    return d->findLlqQueryCategory(result_title);
}

QueryCategory LlqCommandManager::findLlqSerialJobDetailQueryCategory(const QString &result_label)
{
    return d->findLlqSerialJobDetailQueryCategory(result_label);
}

QueryCategory LlqCommandManager::findLlqParellelJobDetailQueryCategory(const QString &result_label)
{
    return d->findLlqParellelJobDetailQueryCategory(result_label);
}

QueryModel *LlqCommandManager::buildLlqQueryModelFromResponse(const QString &response)
{
    return d->buildLlqQueryModelFromResponse(response);
}

QueryModel *LlqCommandManager::buildLlqQueryModelFromResponse(const QJsonDocument &response)
{
    return d->buildLlqQueryModelFromResponse(response);
}

LlqCommandManager::LlqCommandManager(QObject *parent) : QObject(parent)
{
    llq_command_manager_instance = this;
    d = new LlqCommandManagerPrivate{this};
}
