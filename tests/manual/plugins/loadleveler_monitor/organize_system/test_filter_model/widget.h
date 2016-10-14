#pragma once

#include <QWidget>
#include <QPointer>

#include <memory>

namespace LoadLevelerMonitor{
namespace Model{
class LlqCommandManager;
class QueryModel;
}

namespace OrganizeSystem{
class Filter;
class FilterQueryModel;
}
}

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_owner_filter_button_clicked(bool checked);

    void on_date_filter_button_clicked(bool checked);

private:
    void init();

    Ui::Widget *ui;
    QPointer<LoadLevelerMonitor::Model::LlqCommandManager> ll_manager_;
    QPointer<LoadLevelerMonitor::Model::QueryModel> model_;

    QPointer<LoadLevelerMonitor::OrganizeSystem::FilterQueryModel> filter_query_model_;

    std::shared_ptr<LoadLevelerMonitor::OrganizeSystem::Filter> owner_filter_;
    std::shared_ptr<LoadLevelerMonitor::OrganizeSystem::Filter> date_filter_;
};
