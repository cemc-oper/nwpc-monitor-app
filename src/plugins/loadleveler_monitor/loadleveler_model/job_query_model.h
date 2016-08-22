#pragma once

#include "llq_category.h"

#include <QStandardItemModel>
#include <QJsonObject>
#include <QVector>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class JobQueryModel : public QStandardItemModel
{
    Q_OBJECT
public:
    JobQueryModel(QObject *parent=0);
    ~JobQueryModel();

    void setCategoryList(const QVector<LlqQueryCategory> &category_list);

    static JobQueryModel *buildFromLlqQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);
    static JobQueryModel *buildFromLlqDetailQueryResponse(const QStringList& lines, QObject *parent = Q_NULLPTR);

signals:

public slots:

private:
    QVector<LlqQueryCategory> category_list_;

};

}
}
