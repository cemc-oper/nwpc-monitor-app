#include "file_viewer_widget.h"
#include "ui_file_viewer_widget.h"

#include "../loadleveler_monitor_plugin.h"
#include "../loadleveler_client.h"

#include <QActionGroup>
#include <QWebEnginePage>
#include <QScrollBar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

#include <string>
#include <algorithm>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Widgets;

FileViewerWidget::FileViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileViewerWidget),
    is_scroll_to_end_{false},
    style_action_group_{new QActionGroup{this}},
    web_page_{new QWebEnginePage{this}}
{
    ui->setupUi(this);
    setupActions();

    ui->web_engine_view->setPage(web_page_);
    web_page_->load(QUrl("qrc:/loadleveler_monitor/web/static/file_viewer_text_browser.html"));
    setAttribute(Qt::WA_DeleteOnClose);

    setupStyle();
}

FileViewerWidget::~FileViewerWidget()
{
    delete ui;
}

void FileViewerWidget::setRequestArguments(const QMap<QString, QString> args)
{
    request_args_ = args;
}

void FileViewerWidget::setFilePath(const QString &path)
{
    ui->file_path_line_edit->setText(path);
}

void FileViewerWidget::setFileContext(const QString &context)
{
    ui->file_context_browser->setText(context);
    if(is_scroll_to_end_)
    {
        scrollToEnd();
    }
    // TODO: replace single backslash to double backslash
    QString escaped = context;
    escaped.replace(QLatin1String("\n"), QLatin1String("\\n"));
    escaped.replace(QLatin1String("\""), QLatin1String("\\\""));
    QString script = "updateCode(\"" + escaped +"\");";
    web_page_->runJavaScript(script);

}

void FileViewerWidget::receiveResponse(const QString &response)
{
    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[FileViewerWidget::slotReceiveResponse] result is not a json string.";
        return;
    }

    QJsonObject result_object = doc.object();

    QString file_context = result_object["data"].toObject()["response"].toObject()["text"].toString();
    setFileContext(file_context);
}

void FileViewerWidget::slotStyleActionTriggered(QAction *action)
{
    int index = style_action_list_.indexOf(action);
    if(index != -1)
    {
        ui->file_content_viewer_stacked_widget->setCurrentIndex(index);
    }
    else
    {
        qWarning()<<"[FileViewerWidget::slotStyleActionTriggered] action don't find in action list:"<<action;
    }
}

void FileViewerWidget::slotScrollToEnd(bool flag)
{
    is_scroll_to_end_ = flag;
    if(flag)
    {
        scrollToEnd();
        connect(ui->file_context_browser, &QTextBrowser::textChanged, this, &FileViewerWidget::scrollToEnd);
    }
    else
    {
        disconnect(ui->file_context_browser, &QTextBrowser::textChanged, this, &FileViewerWidget::scrollToEnd);
    }
}

void FileViewerWidget::scrollToEnd()
{
    ui->file_context_browser->verticalScrollBar()->setValue(ui->file_context_browser->verticalScrollBar()->maximum());
}

void FileViewerWidget::setupActions()
{
    ui->refresh_tool_button->setDefaultAction(ui->action_refresh);
    connect(ui->action_refresh, &QAction::triggered, [=](bool){
        LoadLevelerMonitorPlugin::client()->runFileCommand(request_args_, this);
    });

    ui->line_wrap_tool_button->setDefaultAction(ui->action_line_wrap);
    connect(ui->action_line_wrap, &QAction::toggled, [=](bool flag){
        if(flag)
            ui->file_context_browser->setLineWrapMode(QTextEdit::WidgetWidth);
        else
            ui->file_context_browser->setLineWrapMode(QTextEdit::NoWrap);
    });

    ui->scroll_to_end_button->setDefaultAction(ui->action_scroll_to_end);
    connect(ui->action_scroll_to_end, &QAction::triggered, this, &FileViewerWidget::slotScrollToEnd);

    connect(ui->close_button, &QPushButton::clicked, this, &FileViewerWidget::close);
}

void FileViewerWidget::setupStyle()
{
    style_action_list_.append(ui->action_text_style);
    style_action_list_.append(ui->action_web_style);

    foreach(QAction* action, style_action_list_)
    {
        style_action_group_->addAction(action);
    }

    connect(style_action_group_, &QActionGroup::triggered, this, &FileViewerWidget::slotStyleActionTriggered);
    ui->action_text_style->activate(QAction::Trigger);

    ui->text_style_tool_button->setDefaultAction(ui->action_text_style);
    ui->web_style_tool_button->setDefaultAction(ui->action_web_style);
}
