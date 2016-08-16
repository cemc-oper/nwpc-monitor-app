#pragma once

#include "../core_plugin_global.h"

#include <QObject>
#include <QString>
#include <QPointer>
#include <QWidget>

namespace Core{

namespace PerspectiveSystem{

/**
 * @brief IPerspective，视图接口类，代表一个 perspective 视图。
 */
class CORE_PLUGIN_EXPORT IPerspective : public QObject
{
    Q_OBJECT
public:
    explicit IPerspective(QObject *parent = 0);

    virtual QString id() const;
    virtual void setId(const QString &id);

    virtual QString displayName() const;
    virtual void setDisplayName(const QString &display_name);

    virtual QWidget* widget() const;
    virtual void setWidget(QWidget* widget);

signals:

public slots:

private:
    QString id_;
    QString display_name_;
    QPointer<QWidget> widget_;

};

}

}
