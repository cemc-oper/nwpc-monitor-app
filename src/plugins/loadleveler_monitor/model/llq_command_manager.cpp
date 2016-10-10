#include "llq_command_manager.h"
#include "llq_command_manager_private.h"

#include "query_model.h"

#include "../chart/category_model_processor.h"

using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;

static LlqCommandManager *llq_command_manager_instance = nullptr;
static LlqCommandManagerPrivate *d = nullptr;

LlqCommandManager *LlqCommandManager::instance()
{
    return llq_command_manager_instance;
}

void LlqCommandManager::initialize()
{
    Q_ASSERT(d);
    d->initCategoryList();
    d->initModelProcessor();
}

QueryCategoryList LlqCommandManager::defaultCategoryList()
{
    return d->default_query_category_list_;
}

QueryCategoryList LlqCommandManager::serialJobDetailQueryCategoryList()
{
    return d->serial_job_detail_category_list_;
}

QueryCategoryList LlqCommandManager::parellelJobDetailQueryCategoryList()
{
    return d->parallel_job_detail_category_list_;
}

QueryCategory LlqCommandManager::findDefaultQueryCategory(const QString &label)
{
    return d->findQueryCategory(label);
}

QueryCategory LlqCommandManager::findSerialJobDetailQueryCategory(const QString &label)
{
    return d->findSerialJobDetailQueryCategory(label);
}

QueryCategory LlqCommandManager::findParellelJobDetailQueryCategory(const QString &label)
{
    return d->findParellelJobDetailQueryCategory(label);
}

QueryModel *LlqCommandManager::buildQueryModelFromResponse(const QString &response_str)
{
    return d->buildQueryModelFromResponse(response_str);
}

QueryModel *LlqCommandManager::buildQueryModelFromResponse(const QJsonDocument &response_doc)
{
    return d->buildQueryModelFromResponse(response_doc);
}

QSet<ModelProcessor *> &LlqCommandManager::processorList()
{
    return d->processorList();
}

QSet<ProcessorCondition *> &LlqCommandManager::processorConditionList()
{
    return d->processorConditionList();
}

QMultiMap<ProcessorCondition *, ModelProcessor *> &LlqCommandManager::processorMap()
{
    return d->processorMap();
}

LlqCommandManager::LlqCommandManager(QObject *parent) : QObject(parent)
{
    llq_command_manager_instance = this;
    d = new LlqCommandManagerPrivate{this};
}
