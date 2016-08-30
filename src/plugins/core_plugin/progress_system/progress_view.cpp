#include "progress_view.h"
#include "ui_progress_view.h"
#include "progress_item_widget.h"

#include <QToolBar>

using namespace Core::ProgressSystem;

ProgressView::ProgressView(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::ProgressView},
    tool_bar_{new QToolBar{this}}
{
    ui->setupUi(this);
    setupActions();
    setupToolBar();
}

ProgressView::~ProgressView()
{
    delete ui;
}

void ProgressView::addProgressItemWidget(QWidget *widget)
{
    ui->progress_layout->insertWidget(0, widget);
}

void ProgressView::slotClearFinishedProgress()
{
    QList<ProgressItemWidget *> finished_widgets;
    for(int i=0; i < ui->progress_layout->count(); i++)
    {
        QWidget * widget = ui->progress_layout->itemAt(i)->widget();
        if(!widget)
            continue;
        ProgressItemWidget *item_widget = qobject_cast<ProgressItemWidget*>(widget);
        if(!item_widget)
            continue;
        if(!item_widget->isProgressFinished())
            continue;
        finished_widgets.append(item_widget);
    }
    foreach(ProgressItemWidget *widget, finished_widgets)
    {
        ui->progress_layout->removeWidget(widget);
        widget->deleteLater();
    }
}

void ProgressView::setupActions()
{
    connect(ui->action_clear_all_finished, &QAction::triggered, this, &ProgressView::slotClearFinishedProgress);
}

void ProgressView::setupToolBar()
{
    ui->tool_bar_layout->addWidget(tool_bar_);
    tool_bar_->addAction(ui->action_clear_all_finished);
}
