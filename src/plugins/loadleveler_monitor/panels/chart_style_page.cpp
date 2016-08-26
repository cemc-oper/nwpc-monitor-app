#include "chart_style_page.h"
#include "ui_chart_style_page.h"

#include <QtCharts/QChart>
#include <QActionGroup>
#include <QToolButton>

using namespace LoadLevelerMonitor::Panels;
using namespace QtCharts;

ChartStylePage::ChartStylePage(QWidget *parent) :
    StylePage{parent},
    ui(new Ui::ChartStylePage)
{
    ui->setupUi(this);
}

ChartStylePage::~ChartStylePage()
{
    delete ui;
}

void ChartStylePage::clear()
{
    // clean chart type layout
    QLayoutItem *child;
    while ((child = ui->chart_type_layout->takeAt(0)) != 0) {
        QWidget * child_widget = child->widget();
        QToolButton *tool_button = qobject_cast<QToolButton *>(child_widget);
        if(tool_button != 0)
        {
            tool_button->deleteLater();
        }
        delete child;
    }
}

void ChartStylePage::setChartTypeActionGroup(QPointer<QActionGroup> action_group)
{
    foreach(QAction *action, action_group->actions())
    {
        QToolButton *tool_button = new QToolButton{this};
        tool_button->setDefaultAction(action);
        int current_column_count = ui->chart_type_layout->columnCount();
        ui->chart_type_layout->addWidget(tool_button, 0, current_column_count);
    }
    QSpacerItem *spacer_item = new QSpacerItem{40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum};
    ui->chart_type_layout->addItem(spacer_item, 0, ui->chart_type_layout->columnCount(), 1, 1);
}

void ChartStylePage::setChart(QChart *chart)
{
    Q_ASSERT(chart);
    QChart *old_chart = ui->chart_view->chart();
    if(old_chart)
        old_chart->deleteLater();
    ui->chart_view->setChart(chart);
}
