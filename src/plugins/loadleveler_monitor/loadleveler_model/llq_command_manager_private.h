#pragma once

#include "llq_category.h"

#include <QVector>
#include <QObject>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class LlqCommandManager;

class LlqCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlqCommandManagerPrivate(LlqCommandManager *parent = 0);

    void initLlqCategoryList();

    QVector<LlqCategory> llqCategoryList();

    LlqCategory findCategory(const QString result_title);

signals:

public slots:

private:
    LlqCommandManager *p;

    QVector<LlqCategory> llq_category_list_;

    friend class LlqCommandManager;
};

}

}
