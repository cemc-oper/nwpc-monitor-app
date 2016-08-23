#pragma once

#include <QWidget>
#include <QPointer>
#include <QMap>

QT_BEGIN_NAMESPACE
class QButtonGroup;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace LoadLevelerModel{
class QueryModel;
}

namespace Ui {
class LoadLevelerMonitorWidget;
}

class LoadLevelerMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadLevelerMonitorWidget(QWidget *parent = 0);
    ~LoadLevelerMonitorWidget();

    QMap<QString, QString> getSessionArguments();

private slots:

private:
    Ui::LoadLevelerMonitorWidget *ui;

    QPointer<QButtonGroup> panel_button_group_;
};

}
