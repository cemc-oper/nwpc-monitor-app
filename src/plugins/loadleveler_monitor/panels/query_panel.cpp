#include "query_panel.h"
#include "ui_query_panel.h"

#include "../model/query_model.h"

#include "../chart/model_processor.h"

#include "../loadleveler_monitor_widget.h"

#include <QActionGroup>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QtCharts/QChart>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::Panels;
using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor::Chart;
using namespace QtCharts;

QueryPanel::QueryPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryPanel),
    style_action_group_{new QActionGroup{this}},
    template_action_group_{new QActionGroup{this}},
    chart_type_action_group_{new QActionGroup{this}}
{
    ui->setupUi(this);

    ui->query_command_frame->hide();
    ui->query_time_frame->hide();

    connect(ui->query_button, &QPushButton::clicked,
            this, &QueryPanel::slotRequestQuery);

    connect(ui->argument_edit, &QLineEdit::returnPressed,
            this, &QueryPanel::slotRequestQuery);

    setupTemplate();
    setupStyle();
}

QueryPanel::~QueryPanel()
{
    delete ui;
    if(query_model_){
        query_model_->deleteLater();
    }
}

void QueryPanel::setMonitorWidget(LoadLevelerMonitorWidget *widget)
{
    monitor_widget_ = widget;
}


void QueryPanel::slotStyleActionTriggered(QAction *action)
{
    int index = style_action_list_.indexOf(action);
    if(index != -1)
        ui->view_area_stacked_widget->setCurrentIndex(index);
    else
    {
        qWarning()<<"[QueryPanel::slotStyleActionTriggered] action don't find in action list:"<<action;
    }
}

void QueryPanel::setupStyle()
{
    qDebug()<<"[QueryPanel::setupStyle]";
}

void QueryPanel::setupTemplate()
{
    qDebug()<<"[QueryPanel::setupTemplate]";
}

void QueryPanel::slotTemplateActionTriggered(QAction *action)
{
    int index = template_action_list_.indexOf(action);
    if(index != -1)
    {
        ui->argument_edit->setText(action->data().toString());
    }
    else
    {
        qWarning()<<"[QueryPanel::slotTemplateActionTriggered] action don't find in action list:"<<action;
    }
}

void QueryPanel::setTableStyleVisibility(bool is_visible)
{
    ui->table_style_button->setHidden(!is_visible);
}

void QueryPanel::setChartStyleVisibility(bool is_visible)
{
    ui->chart_style_button->setHidden(!is_visible);
}

void QueryPanel::setTextStyleVisibility(bool is_visible)
{
    ui->text_style_button->setHidden(!is_visible);
}

void QueryPanel::setRequestCommandLabel(const QJsonObject &request_object)
{
    QString command = request_object["command"].toString();
    QJsonArray arguments = request_object["arguments"].toArray();
    QStringList arg_list;
    foreach(QJsonValue an_argument, arguments)
    {
        arg_list.append(an_argument.toString());
    }
    ui->query_command_label->setText(command + " " + arg_list.join(" "));
    ui->query_command_frame->show();
}

void QueryPanel::setRequestTimeLabel(const QDateTime &request_time, const QDateTime &finish_time)
{
    qint64 interval_seconds = request_time.msecsTo(finish_time);
    ui->query_time_label->setText(QString::number(interval_seconds/1000.0) + " seconds");
    ui->query_time_frame->show();
}

void QueryPanel::showChart(QAction *chart_type_action)
{
    ModelProcessor *processor = chart_type_action_map_[chart_type_action];
    processor->setQueryModel(query_model_);

    QChart *query_chart = processor->generateChart();
    if(!query_chart)
    {
        qWarning()<<"[QueryPanel::showChart] chart is null";
        return;
    }

    ui->chart_style_page->setChart(query_chart);
}

void QueryPanel::setQueryModel(QPointer<QueryModel> query_model)
{
    if(query_model_)
    {
        ui->table_style_page->setModel(nullptr);
        query_model_->deleteLater();
    }
    query_model_ = query_model;

    ui->table_style_page->setModel(query_model_);
}

void QueryPanel::updateTextStylePage(const QString &str)
{
    setTextStyleVisibility(true);
    ui->text_sytel_page->setText(str);
}
