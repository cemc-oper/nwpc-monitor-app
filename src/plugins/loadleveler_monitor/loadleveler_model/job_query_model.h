#pragma once

#include <QStandardItemModel>
#include <QJsonObject>

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{

class JobQueryModel : public QStandardItemModel
{
    Q_OBJECT
public:
    JobQueryModel(QObject *parent=0);

    ~JobQueryModel();

    static JobQueryModel *buildFromLlqQuery(const QJsonObject& data, QObject *parent = Q_NULLPTR);

signals:

public slots:

private:

};

}
}
