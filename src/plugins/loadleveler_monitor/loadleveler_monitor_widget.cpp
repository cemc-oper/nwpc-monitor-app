#include "loadleveler_monitor_widget.h"
#include "ui_loadleveler_monitor_widget.h"

#include "loadleveler_monitor_plugin.h"
#include "loadleveler_client.h"

#include "client_command_widget.h"

#include "loadleveler_model/job_query_model.h"
#include "loadleveler_model/job_query_item.h"

#include <QMap>
#include <QMenu>
#include <QtDebug>

using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::LoadLevelerModel;

LoadLevelerMonitorWidget::LoadLevelerMonitorWidget(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::LoadLevelerMonitorWidget},
    job_query_model_{nullptr}
{
    ui->setupUi(this);

    connect(ui->check_all_button, &QPushButton::clicked,
            [=](){
                changeAllItemsCheckState(Qt::Checked);
            }
    );

    connect(ui->uncheck_all_button, &QPushButton::clicked,
            [=](){
                changeAllItemsCheckState(Qt::Unchecked);
            }
    );

    connect(ui->llq_query_button, &QPushButton::clicked,
            this, &LoadLevelerMonitorWidget::slotRequestQuery);

    connect(ui->llq_argument_edit, &QLineEdit::editingFinished,
            this, &LoadLevelerMonitorWidget::slotRequestQuery);

}

LoadLevelerMonitorWidget::~LoadLevelerMonitorWidget()
{
    delete ui;
    if(job_query_model_){
        job_query_model_->deleteLater();
    }
}

void LoadLevelerMonitorWidget::setJobQueryModel(QPointer<JobQueryModel> job_query_model)
{
    if(job_query_model_)
    {
        ui->llq_table_view->setModel(0);
        job_query_model_->deleteLater();
    }
    job_query_model_ = job_query_model;

    ui->llq_table_view->setModel(job_query_model_);

    ui->llq_table_view->horizontalHeader()->setStretchLastSection(true);

    disconnect(ui->llq_table_view, &QTableView::customContextMenuRequested, 0, 0);
    ui->llq_table_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->llq_table_view, &QTableView::customContextMenuRequested,
            this, &LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest);
}

void LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest(const QPoint &pos)
{
    //qDebug()<<"[LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest]";
    QModelIndex index = ui->llq_table_view->indexAt(pos);
    if (index.isValid()) {
        QMenu *context_menu = new QMenu{};
        QAction *detail_action = new QAction{tr("详情")};

        context_menu->addAction(detail_action);
        QAction *action = context_menu->exec(ui->llq_table_view->mapToGlobal(pos));

        if(action == detail_action)
        {
            QModelIndex id_index = index.sibling(index.row(), 1);
            if(index.isValid())
            {
                QStandardItem *id_item = job_query_model_->itemFromIndex(id_index);
                QString id = id_item->text();
                qDebug()<<"[LoadLevelerMonitorWidget::slotLlqQueryRecordContextMenuRequest]"<<id;
                QMap<QString, QString> args;
                args["host"] = ui->host_edit->text();
                args["port"] = ui->port_edit->text();
                args["user"] = ui->user_edit->text();
                args["password"] = ui->password_edit->text();
                args["command"] = "llq -l "+id;

                //TODO: 创建一个弹出窗口，接收命令执行结果，将窗口传递给 client。
                ClientCommandWidget *command_widget = new ClientCommandWidget();
                command_widget->show();

                LoadLevelerMonitorPlugin::client()->runCommand(args, command_widget);
            }
        }
        delete context_menu;
        delete detail_action;
    }

}

void LoadLevelerMonitorWidget::slotRequestQuery()
{
    QMap<QString, QString> args;
    args["host"] = ui->host_edit->text();
    args["port"] = ui->port_edit->text();
    args["user"] = ui->user_edit->text();
    args["password"] = ui->password_edit->text();
    args["command"] = "llq";
    QString arg_string = ui->llq_argument_edit->text();
    if(!arg_string.isEmpty())
        args["command"] += " "+arg_string;

    LoadLevelerMonitorPlugin::client()->runLlqCommand(args);
}

void LoadLevelerMonitorWidget::changeAllItemsCheckState(Qt::CheckState check_state)
{
    QStandardItem * root_item = job_query_model_->invisibleRootItem();
    int row_count = root_item->rowCount();
    for(int i=0; i<row_count; i++)
    {
        root_item->child(i, 0)->setCheckState(check_state);
    }

}
