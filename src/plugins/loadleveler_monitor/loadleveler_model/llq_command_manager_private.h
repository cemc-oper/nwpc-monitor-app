#pragma once

#include "llq_category.h"

#include <QVector>
#include <QObject>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class LlqCommandManager;
class JobQueryModel;

class LlqCommandManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LlqCommandManagerPrivate(LlqCommandManager *parent = 0);

    void initLlqCategoryList();

    QVector<LlqCategory> llqCategoryList();
    LlqCategory findCategory(const QString result_title);

    JobQueryModel *buildLlqQueryModelFromResponse(const QString &response_str);
    JobQueryModel *buildLlqQueryModel(const QString &output);

signals:

public slots:

private:
    LlqCommandManager *p;

    QVector<LlqCategory> llq_category_list_;

    friend class LlqCommandManager;
};

}

}
