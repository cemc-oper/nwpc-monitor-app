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
    const QString Id{};
    const QString Name{};
    const QStringList PathList{};

    const Qt::DockWidgetArea DockLocation{Qt::BottomDockWidgetArea};
};

}

}
