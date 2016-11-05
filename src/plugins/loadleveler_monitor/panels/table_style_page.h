#pragma once

#include "style_page.h"
#include "../loadleveler_monitor_global.h"

#include <QPointer>
#include <QItemSelection>


QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

namespace LoadLevelerMonitor{

namespace Model{
class QueryModel;
}

namespace Panels{

namespace Ui {
class TableStylePage;
}

class LOADLEVELER_MONITOR_EXPORT TableStylePage : public StylePage
{
    Q_OBJECT

public:
    explicit TableStylePage(QWidget *parent = 0);
    ~TableStylePage();

    void clear();
    void setModel(QPointer<Model::QueryModel> query_model);
    void setSummaryModel(QPointer<QStandardItemModel> summary_model);

    void setOperationButtons(QVector<QPointer<QAction>> action_list);

signals:
    void signalQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index);

private slots:
    void slotUpdateTableViewSelection(const QItemSelection &selected, const QItemSelection &deselected);

private:
    void clearOperationButtons();

    QPointer<Model::QueryModel> query_model_;
    QPointer<QStandardItemModel> summary_model_;
    Ui::TableStylePage *ui;
};

}

}
