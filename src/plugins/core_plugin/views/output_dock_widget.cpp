#include "output_dock_widget.h"
#include "ui_output_dock_widget.h"

#include <view_system/view_spec.h>
#include <view_system/view_manager.h>
#include <view_system/dock_view.h>

#include <QToolBar>
#include <QScrollBar>
#include <QTime>
#include <QtDebug>

using namespace Core::Views;
using namespace Core::ViewSystem;

const QString OutputDockWidget::GeneralPanelId{"General"};

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
    //ui->output_text->insertHtml("<p><b>" + text + "</b></p>");
    //qDebug()<<ui->output_text->toHtml();
}

void OutputDockWidget::appendInfo(const QString &text)
{
    ui->output_text->append(QTime::currentTime().toString("hh:mm:ss") + " INFO " + text);
}

void OutputDockWidget::appendWarning(const QString &text)
{
    ui->output_text->append(QTime::currentTime().toString("hh:mm:ss") + " WARNING " + text);
}

void OutputDockWidget::appendError(const QString &text)
{
    ui->output_text->append(QTime::currentTime().toString("hh:mm:ss") + " ERROR " + text);
}

void OutputDockWidget::info(const QString &output_id, const QString &text)
{

    OutputDockWidget *output_dock_widget = OutputDockWidget::outputDockWidget();
    if(output_dock_widget)
    {
        output_dock_widget->appendInfo(text);
    }
}

void OutputDockWidget::warning(const QString &output_id, const QString &text)
{
    OutputDockWidget *output_dock_widget = OutputDockWidget::outputDockWidget();
    if(output_dock_widget)
    {
        output_dock_widget->appendWarning(text);
    }
}

void OutputDockWidget::error(const QString &output_id, const QString &text)
{
    OutputDockWidget *output_dock_widget = OutputDockWidget::outputDockWidget();
    if(output_dock_widget)
    {
        output_dock_widget->appendError(text);
    }
}

OutputDockWidget *OutputDockWidget::outputDockWidget(const QString &output_panel_id)
{
    ViewSpec *output_view_spec = ViewManager::viewSpecFromPath("/General/Output");
    if(!output_view_spec)
    {
        qWarning()<<"[OutputDockWidget::outputDockWidget] can't find output view ";
        return nullptr;
    }
    else
    {
        DockView *output_dock_view = static_cast<DockView*>(output_view_spec->view());
        OutputDockWidget *output_dock_widget = static_cast<OutputDockWidget*>(output_dock_view->dockWidget());
        return output_dock_widget;
    }
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
    ui->action_scroll_to_end->setChecked(true);
}

void OutputDockWidget::setupToolBar()
{
    ui->tool_bar_layout->addWidget(tool_bar_);
    tool_bar_->addAction(ui->action_scroll_to_end);
    tool_bar_->addAction(ui->action_warp_line);
    tool_bar_->addAction(ui->action_clear);
}
