#include "job_detail_widget.h"
#include "ui_job_detail_widget.h"

#include <QActionGroup>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace LoadlevelerMonitor::Widgets;

JobDetailWidget::JobDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JobDetailWidget),
    style_action_group_{new QActionGroup{this}}
{
    ui->setupUi(this);
    setupStyleActions();
}

JobDetailWidget::~JobDetailWidget()
{
    delete ui;
}

void JobDetailWidget::setJobId(const QString &job_id)
{
    ui->job_id_line_edit->setText(job_id);
}

void JobDetailWidget::receiveResponse(const QString &response)
{
    setResponseStylePage(response);

    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    if(!doc.isObject())
    {
        qDebug()<<"[JobDetailWidget::receiveResponse] result is not a json string.";
        return;
    }

    QJsonObject result_object = doc.object();

//    QString error_message = result_object["data"].toObject()["response"].toObject()["message"].toObject()["error_output"].toString();
//    setErrorOutputText(error_message);

    QString output_message = result_object["data"].toObject()["response"].toObject()["message"].toObject()["output"].toString();
    setOutputStylePage(output_message);
}

void JobDetailWidget::slotStyleActionTriggered(QAction *action)
{
    int index = style_action_list_.indexOf(action);
    if(index != -1)
        ui->stacked_widget->setCurrentIndex(index);
    else
    {
        qWarning()<<"[JobDetailWidget::slotStyleActionTriggered] action don't find in action list:"<<action;
    }
}

void JobDetailWidget::setupStyleActions()
{
    style_action_list_.append(ui->action_output_style);
    style_action_list_.append(ui->action_tree_style);
    style_action_list_.append(ui->action_response_style);

    foreach(QAction* action, style_action_list_)
    {
        style_action_group_->addAction(action);
    }

    connect(style_action_group_, &QActionGroup::triggered, this, &JobDetailWidget::slotStyleActionTriggered);

    ui->action_output_style->activate(QAction::Trigger);

    // style button
    ui->output_style_button->setDefaultAction(ui->action_output_style);
    ui->tree_style_button->setDefaultAction(ui->action_tree_style);
    ui->response_style_button->setDefaultAction(ui->action_response_style);
}

void JobDetailWidget::setResponseStylePage(const QString &response)
{
    ui->response_text_browser->setText(response);
}

void JobDetailWidget::setOutputStylePage(const QString &output)
{
    ui->output_text_browser->setText(output);
}
