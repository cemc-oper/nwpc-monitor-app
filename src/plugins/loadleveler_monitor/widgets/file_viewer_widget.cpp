#include "file_viewer_widget.h"
#include "ui_file_viewer_widget.h"

#include "../loadleveler_monitor_plugin.h"
#include "../loadleveler_client.h"

//#include <QWebEnginePage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Widgets;

FileViewerWidget::FileViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileViewerWidget)//,
//    web_page_{new QWebEnginePage{this}}
{
    ui->setupUi(this);
    ui->refresh_tool_button->setDefaultAction(ui->action_refresh);

    connect(ui->action_refresh, &QAction::triggered, [=](bool){
        LoadLevelerMonitorPlugin::client()->runFileCommand(request_args_, this);
    });

//    ui->web_engine_view->setPage(web_page_);
//    web_page_->load(QUrl("qrc:/loadleveler_monitor/web/static/file_viewer_text_browser.html"));
    setAttribute(Qt::WA_DeleteOnClose);
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
