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

    static QVector<QueryCategory> llqCategoryList();
    static QVector<QueryCategory> llqSerialJobDetailQueryCategoryList();
    static QVector<QueryCategory> llqParellelJobDetailQueryCategoryList();

    static QueryCategory findLlqDefaultQueryCategory(const QString result_title);
    static QueryCategory findLlqSerialJobDetailQueryCategory(const QString &result_label);
    static QueryCategory findLlqParellelJobDetailQueryCategory(const QString &result_label);

    static QueryModel *buildLlqQueryModelFromResponse(const QString &response);
    static QueryModel *buildLlqQueryModelFromResponse(const QJsonDocument &response);

signals:

public slots:

public:
    explicit LlqCommandManager(QObject *parent = 0);

    friend class LoadLevelerMonitorPlugin;
};

}

}
