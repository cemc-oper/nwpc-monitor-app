#include "llq_panel.h"
#include "ui_llq_panel.h"

#include <QActionGroup>
#include <QtDebug>

using namespace LoadLevelerMonitor::Panels;

LlqPanel::LlqPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LlqPanel),
    style_action_group_{new QActionGroup{this}}
{
    ui->setupUi(this);

    setupStyle();
}

LlqPanel::~LlqPanel()
{
    delete ui;
}

void LlqPanel::slotStyleActionTriggered(QAction *action)
{
    int index = style_action_list_.indexOf(action);
    if(index != -1)
        ui->view_area_stacked_widget->setCurrentIndex(index);
    else
    {
        qWarning()<<"[LlqPanel::slotStyleActionTriggered] action don't find in action list:"<<action;
    }
}

void LlqPanel::setupStyle()
{
    ui->table_style_button->setDefaultAction(ui->action_table_style);
    ui->chart_style_button->setDefaultAction(ui->action_chart_style);
    ui->text_style_button->setDefaultAction(ui->action_text_style);

    style_action_list_.clear();
    style_action_list_.append(ui->action_table_style);
    style_action_list_.append(ui->action_chart_style);
    style_action_list_.append(ui->action_text_style);

    foreach(QAction *action, style_action_list_)
    {
        style_action_group_->addAction(action);
    }

    connect(style_action_group_, &QActionGroup::triggered, this, &LlqPanel::slotStyleActionTriggered);

    ui->action_table_style->setChecked(Qt::Checked);
    ui->view_area_stacked_widget->setCurrentIndex(0);
}
