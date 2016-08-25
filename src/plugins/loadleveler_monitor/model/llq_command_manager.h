#pragma once

#include "../loadleveler_monitor_global.h"

#include "query_category.h"
#include "query_category_list.h"

#include <QObject>
#include <QJsonDocument>

namespace LoadLevelerMonitor{

namespace Chart{
class ModelCategoryProcessor;
}

class LoadLevelerMonitorPlugin;

namespace Model{

class QueryModel;
class LlqCommandManagerPrivate;

class LOADLEVELER_MONITOR_EXPORT LlqCommandManager : public QObject
{
    Q_OBJECT
public:
    static LlqCommandManager *instance();

    static void initialize();

    static QueryCategoryList defaultCategoryList();
    static QueryCategoryList serialJobDetailQueryCategoryList();
    static QueryCategoryList parellelJobDetailQueryCategoryList();

    static QueryCategory findDefaultQueryCategory(const QString &label);
    static QueryCategory findSerialJobDetailQueryCategory(const QString &label);
    static QueryCategory findParellelJobDetailQueryCategory(const QString &label);

    static QueryModel *buildQueryModelFromResponse(const QString &response_str);
    static QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_doc);

    static Chart::ModelCategoryProcessor *modelDataProcessor();

signals:

public slots:

public:
    explicit LlqCommandManager(QObject *parent = 0);

    friend class LoadLevelerMonitorPlugin;
};

}

}
