#include "progress_view.h"
#include "ui_progress_view.h"

using namespace Core::ProgressSystem;

ProgressView::ProgressView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressView)
{
    ui->setupUi(this);
}

ProgressView::~ProgressView()
{
    delete ui;
}

void ProgressView::addProgressItemWidget(QWidget *widget)
{
    ui->progress_layout->insertWidget(0, widget);
}
