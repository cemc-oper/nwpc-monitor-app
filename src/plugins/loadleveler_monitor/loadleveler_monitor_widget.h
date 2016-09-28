#pragma once

#include <core_plugin/session_system/session.h>

#include <QWidget>
#include <QPointer>
#include <QMap>

QT_BEGIN_NAMESPACE
class QButtonGroup;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

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
    void slotChooseSession();

private:
    void setSession(const Core::SessionSystem::Session &session);

    Ui::LoadLevelerMonitorWidget *ui;

    QPointer<QButtonGroup> panel_button_group_;
};

}
