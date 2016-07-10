#pragma once

#include <QStandardItemModel>
#include <QJsonObject>

namespace SmsMonitor{

namespace SmsModel{

class Bunch : public QStandardItemModel
{
    Q_OBJECT
public:
    Bunch(QObject *parent = Q_NULLPTR);

    static Bunch *buildFromJsonStatus(const QJsonObject& data, QObject *parent = Q_NULLPTR);

private:
    QString owner_;
    QString repo_;
    QString sms_name_;
    QString sms_user_;
};

}

}
