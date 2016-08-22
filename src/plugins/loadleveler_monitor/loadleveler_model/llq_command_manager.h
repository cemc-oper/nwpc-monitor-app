#pragma once

#include "../loadleveler_monitor_global.h"

#include "llq_category.h"
#include <QVector>
#include <QObject>
#include <QJsonDocument>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPlugin;

namespace LoadLevelerModel{

class JobQueryModel;

class LlqCommandManagerPrivate;

class LOADLEVELER_MONITOR_EXPORT LlqCommandManager : public QObject
{
    Q_OBJECT
public:
    static LlqCommandManager *instance();

    static void initialize();

    static QVector<LlqQueryCategory> llqCategoryList();
    static QVector<LlqDetailQueryCategory> llqSerialJobDetailQueryCategoryList();
    static QVector<LlqDetailQueryCategory> llqParellelJobDetailQueryCategoryList();

    LlqDetailQueryCategory findLlqSerialJobDetailQueryCategory(const QString &result_label) const;
    LlqDetailQueryCategory findLlqParellelJobDetailQueryCategory(const QString &result_label) const;

    static LlqQueryCategory findCategory(const QString result_title);

    static JobQueryModel *buildLlqQueryModelFromResponse(const QString &response);
    static JobQueryModel *buildLlqQueryModelFromResponse(const QJsonDocument &response);

signals:

public slots:

public:
    explicit LlqCommandManager(QObject *parent = 0);

    friend class LoadLevelerMonitorPlugin;
};

}

}
