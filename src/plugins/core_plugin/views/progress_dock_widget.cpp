#include "progress_dock_widget.h"
#include "ui_progress_dock_widget.h"

#include <QtDebug>

using namespace Core::Views;
using namespace Core::ViewSystem;

ProgressDockWidget::ProgressDockWidget(QWidget *parent) :
    DockWidget(
        "NwpcMonitor.CorePlugin.View.ProgressDockView",
        tr("Progress"),
        QStringList()<<"General"<<"Progress",
        ":/core/images/progress_view@128x128.png",
        Qt::BottomDockWidgetArea,
        parent
    ),
    ui(new Ui::ProgressDockWidget)
{
    ui->setupUi(this);
}

ProgressDockWidget::~ProgressDockWidget()
{
    delete ui;
}

Core::ProgressSystem::ProgressView *ProgressDockWidget::progressView()
{
    return ui->progress_view;
}
