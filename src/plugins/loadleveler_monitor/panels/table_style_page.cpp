#include "table_style_page.h"
#include "ui_table_style_page.h"
#include "../model/query_model.h"
#include "../model/query_item.h"

#include <util/model_view_util.h>

#include <QMenu>
#include <QAction>
#include <QtDebug>

using namespace LoadLevelerMonitor::Panels;
using namespace LoadLevelerMonitor::Model;

TableStylePage::TableStylePage(QWidget *parent) :
    StylePage{parent},
    ui(new Ui::TableStylePage)
{
    ui->setupUi(this);

    connect(ui->check_all_button, &QPushButton::clicked,
            [=](){
                Util::ModelView::changeAllItemsCheckState(query_model_, Qt::Checked);
            }
    );

    connect(ui->uncheck_all_button, &QPushButton::clicked,
            [=](){
                Util::ModelView::changeAllItemsCheckState(query_model_, Qt::Unchecked);
            }
    );
}

TableStylePage::~TableStylePage()
{
    delete ui;
}

void TableStylePage::clear()
{
    ui->table_view->setModel(nullptr);
}

void TableStylePage::setModel(QPointer<QueryModel> query_model)
{
    query_model_ = query_model;

    ui->table_view->setModel(query_model_);
    if(!query_model_)
    {
        return;
    }

    ui->table_view->horizontalHeader()->setStretchLastSection(true);
    switch(query_model_->queryType())
    {
    case QueryType::LlqDefaultQuery:
        ui->table_view->setColumnWidth(1, 200); // id
        ui->table_view->setColumnWidth(3, 150); //
        break;
    case QueryType::LlqDetailQuery:
        // TODO: 目前无法保留调整过的列宽，每次都恢复到初始状态
        ui->table_view->setColumnWidth(1, 160); // id
        ui->table_view->setColumnWidth(2, 80);
        ui->table_view->setColumnWidth(4, 400);
        break;
    default:
        break;
    }

    ui->table_view->sortByColumn(0, Qt::AscendingOrder);

    disconnect(ui->table_view, &QTableView::customContextMenuRequested, 0, 0);
    ui->table_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table_view, &QTableView::customContextMenuRequested,
            [=](const QPoint &pos){
        emit signalQueryModelContextMenuRequest(ui->table_view->mapToGlobal(pos), ui->table_view->indexAt(pos));
    });
}
