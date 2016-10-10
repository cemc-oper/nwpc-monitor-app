#include "llclass_command_manager.h"
#include "llclass_command_manager_private.h"

#include "query_model.h"

#include "../chart/category_model_processor.h"

using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;

static LlclassCommandManager *llclass_command_manager_instance = nullptr;
static LlclassCommandManagerPrivate *d = nullptr;

LlclassCommandManager *LlclassCommandManager::instance()
{
    return llclass_command_manager_instance;
}

void LlclassCommandManager::initialize()
{
    Q_ASSERT(d);
    d->initCategoryList();
    d->initModelProcessor();
}

QueryCategoryList LlclassCommandManager::defaultCategoryList()
{
    return d->default_query_category_list_;
}

QueryCategoryList LlclassCommandManager::detailQueryCategoryList()
{
    return d->detail_query_category_list_;
}


QueryCategory LlclassCommandManager::findDefaultQueryCategory(const QString &label)
{
    return d->findDefaultQueryCategory(label);
}

QueryCategory LlclassCommandManager::findDetailQueryCategory(const QString &label)
{
    return d->findDetailQueryCategory(label);
}

QueryModel *LlclassCommandManager::buildQueryModelFromResponse(const QString &response_str)
{
    return d->buildQueryModelFromResponse(response_str);
}

QueryModel *LlclassCommandManager::buildQueryModelFromResponse(const QJsonDocument &response_doc)
{
    return d->buildQueryModelFromResponse(response_doc);
}

QSet<ModelProcessor *> &LlclassCommandManager::processorList()
{
    return d->processorList();
}

QSet<ProcessorCondition *> &LlclassCommandManager::processorConditionList()
{
    return d->processorConditionList();
}

QMultiMap<ProcessorCondition *, ModelProcessor *> &LlclassCommandManager::processorMap()
{
    return d->processorMap();
}

LlclassCommandManager::LlclassCommandManager(QObject *parent) : QObject(parent)
{
    llclass_command_manager_instance = this;
    d = new LlclassCommandManagerPrivate{this};
}
