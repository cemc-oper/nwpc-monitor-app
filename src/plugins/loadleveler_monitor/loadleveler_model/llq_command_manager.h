#pragma once

#include "llq_category.h"
#include <QVector>
#include <QObject>

namespace LoadLevelerMonitor{

class LoadLevelerMonitorPlugin;

namespace LoadLevelerModel{

class LlqCommandManagerPrivate;

class LlqCommandManager : public QObject
{
    Q_OBJECT
public:
    static LlqCommandManager *instance();

    static void initialize();

    static QVector<LlqCategory> llqCategoryList();

    static LlqCategory findCategory(const QString result_title);

signals:

public slots:

private:
    explicit LlqCommandManager(QObject *parent = 0);

    friend class LoadLevelerMonitorPlugin;
};

}

}
