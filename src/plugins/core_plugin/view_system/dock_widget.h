#pragma once

#include <QDockWidget>

namespace Core{

namespace ViewSystem{

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(QWidget *parent = 0);

signals:

public slots:

public:
    /**
     * 默认属性，派生类需要重新定义下面的const成员变量
     */

    const QString Id{};
    const QString Name{};
    const QStringList PathList{};

    const Qt::DockWidgetArea DockLocation{Qt::BottomDockWidgetArea};
};

}

}
