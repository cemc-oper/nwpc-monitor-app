#include "llq_command_manager.h"
#include "llq_command_manager_private.h"

#include "job_query_model.h"

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

QVector<LlqQueryCategory> LlqCommandManager::llqCategoryList()
{
    return d->llqCategoryList();
}

QVector<LlqQueryCategory> LlqCommandManager::llqSerialJobDetailQueryCategoryList()
{
    return d->llq_serial_job_detail_category_list_;
}

QVector<LlqQueryCategory> LlqCommandManager::llqParellelJobDetailQueryCategoryList()
{
    return d->llq_parallel_job_detail_category_list_;
}

LlqQueryCategory LlqCommandManager::findLlqSerialJobDetailQueryCategory(const QString &result_label) const
{
    return d->findLlqSerialJobDetailQueryCategory(result_label);
}

LlqQueryCategory LlqCommandManager::findLlqParellelJobDetailQueryCategory(const QString &result_label) const
{
    return d->findLlqParellelJobDetailQueryCategory(result_label);
}

LlqQueryCategory LlqCommandManager::findCategory(const QString result_title)
{
    return d->findLlqQueryCategory(result_title);
}

JobQueryModel *LlqCommandManager::buildLlqQueryModelFromResponse(const QString &response)
{
    return d->buildLlqQueryModelFromResponse(response);
}

JobQueryModel *LlqCommandManager::buildLlqQueryModelFromResponse(const QJsonDocument &response)
{
    return d->buildLlqQueryModelFromResponse(response);
}

LlqCommandManager::LlqCommandManager(QObject *parent) : QObject(parent)
{
    llq_command_manager_instance = this;
    d = new LlqCommandManagerPrivate{this};
}
