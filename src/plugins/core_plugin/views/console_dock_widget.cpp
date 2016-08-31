#include "console_dock_widget.h"
#include "ui_console_dock_widget.h"

#include <view_system/view_spec.h>
#include <view_system/view_manager.h>
#include <view_system/dock_view.h>

#include <QToolBar>
#include <QScrollBar>
#include <QTime>
#include <QtDebug>

using namespace Core::Views;
using namespace Core::ViewSystem;

const QString ConsoleDockWidget::GeneralPanelId{"General"};

ConsoleDockWidget::ConsoleDockWidget(QWidget *parent) :
    Core::ViewSystem::DockWidget(
        "NwpcMonitor.CorePlugin.View.ConsoleDockView",
        tr("Console"),
        QStringList()<<"General"<<"Console",
        ":/core/images/console-view-icon@128x128.png",
        Qt::BottomDockWidgetArea,
        parent
    ),
    ui(new Ui::ConsoleDockWidget),
    tool_bar_{new QToolBar{this}}
{
    ui->setupUi(this);
    setupActions();
    setupToolBar();
}

ConsoleDockWidget::~ConsoleDockWidget()
{
    delete ui;
}

void ConsoleDockWidget::appendText(const QString &text)
{
    ui->output_text->append(text);
    //ui->output_text->insertHtml("<p><b>" + text + "</b></p>");
    //qDebug()<<ui->output_text->toHtml();
}

void ConsoleDockWidget::appendInfo(const QString &text)
{
    ui->output_text->append(QTime::currentTime().toString("hh:mm:ss") + " INFO " + text);
}

void ConsoleDockWidget::appendWarning(const QString &text)
{
    ui->output_text->append(QTime::currentTime().toString("hh:mm:ss") + " WARNING " + text);
}

void ConsoleDockWidget::appendError(const QString &text)
{
    ui->output_text->append(QTime::currentTime().toString("hh:mm:ss") + " ERROR " + text);
}

void ConsoleDockWidget::info(const QString &output_id, const QString &text)
{

    ConsoleDockWidget *output_dock_widget = ConsoleDockWidget::outputDockWidget();
    if(output_dock_widget)
    {
        output_dock_widget->appendInfo(text);
    }
}

void ConsoleDockWidget::warning(const QString &output_id, const QString &text)
{
    ConsoleDockWidget *output_dock_widget = ConsoleDockWidget::outputDockWidget();
    if(output_dock_widget)
    {
        output_dock_widget->appendWarning(text);
    }
}

void ConsoleDockWidget::error(const QString &output_id, const QString &text)
{
    ConsoleDockWidget *output_dock_widget = ConsoleDockWidget::outputDockWidget();
    if(output_dock_widget)
    {
        output_dock_widget->appendError(text);
    }
}

ConsoleDockWidget *ConsoleDockWidget::outputDockWidget(const QString &output_panel_id)
{
    ViewSpec *output_view_spec = ViewManager::viewSpecFromPath("/General/Console");
    if(!output_view_spec)
    {
        qWarning()<<"[ConsoleDockWidget::outputDockWidget] can't find output view ";
        return nullptr;
    }
    else
    {
        DockView *output_dock_view = static_cast<DockView*>(output_view_spec->view());
        ConsoleDockWidget *output_dock_widget = static_cast<ConsoleDockWidget*>(output_dock_view->dockWidget());
        return output_dock_widget;
    }
}

void ConsoleDockWidget::slotScrollToEnd(bool flag)
{
    if(flag)
    {
        slotScroolToEnd();
        connect(ui->output_text, &QTextBrowser::textChanged, this, &ConsoleDockWidget::slotScroolToEnd);
    }
    else
    {
        disconnect(ui->output_text, &QTextBrowser::textChanged, this, &ConsoleDockWidget::slotScroolToEnd);
    }
}

void ConsoleDockWidget::slotScroolToEnd()
{
    ui->output_text->verticalScrollBar()->setValue(ui->output_text->verticalScrollBar()->maximum());
}

void ConsoleDockWidget::setupActions()
{
    connect(ui->action_warp_line, &QAction::toggled, [=](bool flag){
        if(flag)
            ui->output_text->setLineWrapMode(QTextEdit::WidgetWidth);
        else
            ui->output_text->setLineWrapMode(QTextEdit::NoWrap);
    });

    connect(ui->action_clear, &QAction::triggered, [=](bool){
        qDebug()<<"[ConsoleDockWidget] clear output text.";
        ui->output_text->clear();
    });

    connect(ui->action_scroll_to_end, &QAction::toggled, this, &ConsoleDockWidget::slotScrollToEnd);
    ui->action_scroll_to_end->setChecked(true);
}

void ConsoleDockWidget::setupToolBar()
{
    ui->tool_bar_layout->addWidget(tool_bar_);
    tool_bar_->addAction(ui->action_scroll_to_end);
    tool_bar_->addAction(ui->action_warp_line);
    tool_bar_->addAction(ui->action_clear);
}
