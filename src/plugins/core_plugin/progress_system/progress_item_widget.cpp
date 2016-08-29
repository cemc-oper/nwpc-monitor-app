#include "progress_item_widget.h"
#include "ui_progress_item_widget.h"

using namespace Core::ProgressSystem;

ProgressItemWidget::ProgressItemWidget(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::ProgressItemWidget}
{
    ui->setupUi(this);
    ui->title_label->setText("");
    ui->description_label->setText("");
    ui->progress_bar->setValue(0);
}

ProgressItemWidget::~ProgressItemWidget()
{
    delete ui;
}

void ProgressItemWidget::setTitle(const QString &title)
{
    ui->title_label->setText(title);
}

void ProgressItemWidget::setDescription(const QString &description)
{
    ui->description_label->setText(description);
}

void ProgressItemWidget::setProgressValue(int value)
{
    ui->progress_bar->setValue(value);
}

int ProgressItemWidget::getProgressMaxValue() const
{
    return ui->progress_bar->maximum();
}
