#pragma once

#include <QList>
#include <QStandardItem>
#include <QJsonObject>
#include <QMetaType>

namespace SmsMonitor{

namespace SmsModel{

class Node : public QStandardItem
{
public:
    explicit Node();
    explicit Node(const QString &text);

    ~Node();

    enum DataType
    {
        Name = QStandardItem::UserType + 10,
        Status = QStandardItem::UserType + 20,
        Children = QStandardItem::UserType + 30
    };

    static Node *buildFromJsonStatus(const QJsonObject &data);

    virtual QString getNodePath();


    QVariant data(int role = Qt::UserRole + 1) const override;
    void setData(const QVariant &value, int role = Qt::UserRole + 1) override;

signals:

public slots:

private:
    QString name_;
    QString status_;
};

}

}
Q_DECLARE_METATYPE(QList<QStandardItem*>)

