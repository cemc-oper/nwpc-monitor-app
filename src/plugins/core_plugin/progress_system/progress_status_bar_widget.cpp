#include "progress_status_bar_widget.h"
#include "ui_progress_status_bar_widget.h"

using namespace Core::ProgressSystem;

ProgressStatusBarWidget::ProgressStatusBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressStatusBarWidget)
{
    ui->setupUi(this);
    ui->progress_bar->setValue(0);
}

ProgressStatusBarWidget::~ProgressStatusBarWidget()
{
    delete ui;
}

void ProgressStatusBarWidget::setProgressRange(int min_value, int max_value)
{
    ui->progress_bar->setRange(min_value, max_value);
}

void ProgressStatusBarWidget::slotSetProgressValue(int value)
{
    ui->progress_bar->setValue(value);
}
