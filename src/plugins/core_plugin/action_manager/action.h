#pragma once

#include <core_plugin_global.h>

#include <QObject>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace Core{

class CORE_PLUGIN_EXPORT Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QString id, QObject *parent = 0);

    ~Action();

    QString id() const;

    QAction *action() const;
    void setAction(QAction *action);

signals:

public slots:

protected:
    QString id_;
    QPointer<QAction> action_;
};

}
