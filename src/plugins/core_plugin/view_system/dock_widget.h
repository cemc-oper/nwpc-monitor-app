#pragma once

#include <QDockWidget>

namespace Core{

namespace ViewSystem{

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(QWidget *parent = 0);
    DockWidget(
            QString id,
            QString name,
            QStringList path_list,
            QString icon_location,
            Qt::DockWidgetArea dock_location,
            QWidget *parent = 0
    );

    QString Id() const
    {
        return kId;
    }
    QString Name() const
    {
        return kName;
    }
    QStringList PathList() const
    {
        return kPathList;
    }
    QString IconLocation() const
    {
        return kIconLocation;
    }
    Qt::DockWidgetArea DockLocation() const
    {
        return kDockLocation;
    }

signals:

public slots:

protected:
    /**
     * 默认属性，派生类需要重新定义下面的const成员变量
     */
    const QString kId;
    const QString kName;
    const QStringList kPathList;
    const QString kIconLocation;

    const Qt::DockWidgetArea kDockLocation;
};

}

}
