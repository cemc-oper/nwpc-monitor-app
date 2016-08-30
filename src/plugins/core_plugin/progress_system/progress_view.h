#pragma once

#include "../core_plugin_global.h"
#include <QWidget>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QToolBar;
QT_END_NAMESPACE

namespace Core{

namespace ProgressSystem{

namespace Ui {
class ProgressView;
}

class CORE_PLUGIN_EXPORT ProgressView : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressView(QWidget *parent = 0);
    ~ProgressView();

    void addProgressItemWidget(QWidget *widget);

private slots:
    void slotClearFinishedProgress();

private:
    void setupActions();
    void setupToolBar();

    Ui::ProgressView *ui;
    QPointer<QToolBar> tool_bar_;
};

}

}
