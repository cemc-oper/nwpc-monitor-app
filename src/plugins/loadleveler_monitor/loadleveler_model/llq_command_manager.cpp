#include "llq_command_manager.h"
#include "llq_command_manager_private.h"

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

QVector<LlqCategory> LlqCommandManager::llqCategoryList()
{
    return d->llqCategoryList();
}

LlqCategory LlqCommandManager::findCategory(const QString result_title)
{
    return d->findCategory(result_title);
}

LlqCommandManager::LlqCommandManager(QObject *parent) : QObject(parent)
{
    llq_command_manager_instance = this;
    d = new LlqCommandManagerPrivate{this};
}
