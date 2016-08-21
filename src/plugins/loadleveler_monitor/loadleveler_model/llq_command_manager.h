#pragma once

#include "../loadleveler_monitor_global.h"

#include "llq_category.h"
#include <QVector>
#include <QObject>

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

    static QVector<LlqCategory> llqCategoryList();

    static LlqCategory findCategory(const QString result_title);

    static JobQueryModel *buildLlqQueryModelFromResponse(const QString &response);

signals:

public slots:

public:
    explicit LlqCommandManager(QObject *parent = 0);

    friend class LoadLevelerMonitorPlugin;
};

}

}
