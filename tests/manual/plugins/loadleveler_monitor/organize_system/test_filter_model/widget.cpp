#include "widget.h"
#include "ui_widget.h"

#include <loadleveler_monitor/model/query_model.h>
#include <loadleveler_monitor/model/llq_command_manager.h>

#include <loadleveler_monitor/organize_system/filter.h>
#include <loadleveler_monitor/organize_system/filter_query_model.h>
#include <loadleveler_monitor/organize_system/filter_condition.h>
#include <loadleveler_monitor/organize_system/filter_value_checker.h>
#include <loadleveler_monitor/organize_system/filter_value_extractor.h>

#include <QFile>
#include <QTest>
#include <QtDebug>

using namespace LoadLevelerMonitor::Model;
using namespace LoadLevelerMonitor;
using namespace LoadLevelerMonitor::OrganizeSystem;
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    ll_manager_{new LlqCommandManager{this}},
    filter_query_model_{new FilterQueryModel{this}}
{
    ui->setupUi(this);

    init();

    ui->source_table_view->setModel(model_);
    ui->filter_table_view->setModel(filter_query_model_);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    LlqCommandManager::initialize();

    QString response_file_path = QFINDTESTDATA("../data/response.json");
    QString llq_output_file_path = QFINDTESTDATA("../data/llq_output.txt");

    QFile llq_output_file{llq_output_file_path};
    llq_output_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString llq_output{llq_output_file.readAll()};
    llq_output_file.close();

    QFile response_file{response_file_path};
    response_file.open( QIODevice::ReadOnly | QIODevice::Text);
    QByteArray b = response_file.readAll();
    b.replace(QString("\"output\": \"\"").toStdString().c_str(),
              QString("\"output\": \"" + llq_output + "\"").toStdString().c_str());

    model_ = LlqCommandManager::buildQueryModelFromResponse(b);

    // init filter

    // checker
    auto owner_checker = make_shared<StringChecker>();
    owner_checker->setCondition(StringChecker::OperatorType::Equal, "nwp");

    auto date_checker = make_shared<DateTimeChecker>();
    date_checker->setCondition(DateTimeChecker::OperatorType::After, QDateTime{QDate{2016,10,3}, QTime{23,59,59}});

    // extractor
    auto owner_extractor = make_shared<QueryCategoryValueExtractor>();
    owner_extractor->setQueryCategory(LlqCommandManager::defaultCategoryList().categoryFromId(Constant::Llq::Owner));

    auto date_extractor = make_shared<QueryCategoryValueExtractor>();
    date_extractor->setQueryCategory(LlqCommandManager::defaultCategoryList().categoryFromId(Constant::Llq::Submitted));

    // condition
    auto owner_condition = make_shared<FilterCondition>();
    owner_condition->setValueChecker(owner_checker);
    owner_condition->setValueExtractor(owner_extractor);

    auto date_condition = make_shared<FilterCondition>();
    date_condition->setValueChecker(date_checker);
    date_condition->setValueExtractor(date_extractor);

    owner_filter_ = make_shared<Filter>();
    owner_filter_->setCombinationType(Filter::CombinationType::All);
    owner_filter_->addCondition(owner_condition);

    date_filter_ = make_shared<Filter>();
    date_filter_->setCombinationType(Filter::CombinationType::All);
    date_filter_->addCondition(date_condition);

}

void Widget::on_owner_filter_button_clicked(bool checked)
{
    filter_query_model_->clear();
    filter_query_model_->setFilter(owner_filter_);
    filter_query_model_->setSourceModel(model_);
}

void Widget::on_date_filter_button_clicked(bool checked)
{
    filter_query_model_->clear();
    filter_query_model_->setFilter(date_filter_);
    filter_query_model_->setSourceModel(model_);
}
