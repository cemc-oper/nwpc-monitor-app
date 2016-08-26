#pragma once

#include "style_page.h"
#include <QPointer>

QT_BEGIN_NAMESPACE
class QActionGroup;
namespace QtCharts{
class QChart;
}
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace Panels{

namespace Ui {
class ChartStylePage;
}

class ChartStylePage : public StylePage
{
    Q_OBJECT

public:
    explicit ChartStylePage(QWidget *parent = 0);
    ~ChartStylePage();

    void clear();
    void setChartTypeActionGroup(QPointer<QActionGroup> action_group);
    void setChart(QtCharts::QChart *chart);

private:
    Ui::ChartStylePage *ui;
};

}

}
