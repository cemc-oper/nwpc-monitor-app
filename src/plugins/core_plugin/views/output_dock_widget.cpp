#include "output_dock_widget.h"
#include "ui_output_dock_widget.h"

#include <QToolBar>
#include <QScrollBar>
#include <QtDebug>

using namespace Core::Views;

OutputDockWidget::OutputDockWidget(QWidget *parent) :
    Core::ViewSystem::DockWidget(parent),
    ui(new Ui::OutputDockWidget),
    tool_bar_{new QToolBar{this}}
{
    ui->setupUi(this);

    setupActions();
    setupToolBar();
}

OutputDockWidget::~OutputDockWidget()
{
    delete ui;
}

void OutputDockWidget::appendText(const QString &text)
{
    ui->output_text->append(text);
}

void OutputDockWidget::slotScrollToEnd(bool flag)
{
    if(flag)
    {
        slotScroolToEnd();
        connect(ui->output_text, &QTextBrowser::textChanged, this, &OutputDockWidget::slotScroolToEnd);
    }
    else
    {
        disconnect(ui->output_text, &QTextBrowser::textChanged, this, &OutputDockWidget::slotScroolToEnd);
    }
}

void OutputDockWidget::slotScroolToEnd()
{
    ui->output_text->verticalScrollBar()->setValue(ui->output_text->verticalScrollBar()->maximum());
}

void OutputDockWidget::setupActions()
{
    connect(ui->action_warp_line, &QAction::toggled, [=](bool flag){
        if(flag)
            ui->output_text->setLineWrapMode(QTextEdit::WidgetWidth);
        else
            ui->output_text->setLineWrapMode(QTextEdit::NoWrap);
    });

    connect(ui->action_clear, &QAction::triggered, [=](bool flag){
        qDebug()<<"[OutputDockWidget] clear output text.";
        ui->output_text->clear();
    });

    connect(ui->action_scroll_to_end, &QAction::toggled, this, &OutputDockWidget::slotScrollToEnd);
}

void OutputDockWidget::setupToolBar()
{
    ui->tool_bar_layout->addWidget(tool_bar_);
    tool_bar_->addAction(ui->action_scroll_to_end);
    tool_bar_->addAction(ui->action_warp_line);
    tool_bar_->addAction(ui->action_clear);
}
