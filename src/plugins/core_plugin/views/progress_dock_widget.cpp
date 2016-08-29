#include "progress_dock_widget.h"
#include "ui_progress_dock_widget.h"

#include <QtDebug>

using namespace Core::Views;
using namespace Core::ViewSystem;

ProgressDockWidget::ProgressDockWidget(QWidget *parent) :
    DockWidget(parent),
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
