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

    void setCategoryList(const QVector<LlqCategory> &category_list);

    static JobQueryModel *buildFromLlqQuery(const QJsonObject& data, QObject *parent = Q_NULLPTR);
    static JobQueryModel *buildFromLlqResponseLines(const QStringList& lines, QObject *parent = Q_NULLPTR);

signals:

public slots:

private:
    QVector<LlqCategory> category_list_;

};

}
}
