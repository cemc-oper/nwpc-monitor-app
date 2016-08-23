#pragma once

#include "../loadleveler_monitor_global.h"

#include "query_category.h"
#include <QVector>
#include <QObject>
#include <QJsonDocument>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPlugin;

namespace LoadLevelerModel{

class QueryModel;
class LlqCommandManagerPrivate;

class LOADLEVELER_MONITOR_EXPORT LlqCommandManager : public QObject
{
    Q_OBJECT
public:
    static LlqCommandManager *instance();

    static void initialize();

    static QVector<QueryCategory> defaultCategoryList();
    static QVector<QueryCategory> serialJobDetailQueryCategoryList();
    static QVector<QueryCategory> parellelJobDetailQueryCategoryList();

    static QueryCategory findDefaultQueryCategory(const QString &label);
    static QueryCategory findSerialJobDetailQueryCategory(const QString &label);
    static QueryCategory findParellelJobDetailQueryCategory(const QString &label);

    static QueryModel *buildQueryModelFromResponse(const QString &response_str);
    static QueryModel *buildQueryModelFromResponse(const QJsonDocument &response_doc);

signals:

public slots:

public:
    explicit LlqCommandManager(QObject *parent = 0);

    friend class LoadLevelerMonitorPlugin;
};

}

}
