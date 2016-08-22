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

    QVector<LlqQueryCategory> llqCategoryList();
    LlqQueryCategory findCategory(const QString result_title);

    JobQueryModel *buildLlqQueryModelFromResponse(const QString &response_str);
    JobQueryModel *buildLlqQueryModelFromResponse(const QJsonDocument &response_json_document);

signals:

public slots:

private:
    JobQueryModel *buildLlqQueryModel(const QString &output);
    JobQueryModel *buildLlqDetailQueryModel(const QString &output);

    bool isLlqDetailQuery(const QString &command, const QStringList &arguments) const;

    LlqCommandManager *p;

    QVector<LlqQueryCategory> llq_category_list_;

    friend class LlqCommandManager;
};

}

}
