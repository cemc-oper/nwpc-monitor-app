#pragma once

#include "style_page.h"

#include <QPointer>

namespace LoadLevelerMonitor{

namespace Model{
class QueryModel;
}

namespace Panels{

namespace Ui {
class TableStylePage;
}

class TableStylePage : public StylePage
{
    Q_OBJECT

public:
    explicit TableStylePage(QWidget *parent = 0);
    ~TableStylePage();

    void clear();
    void setModel(QPointer<Model::QueryModel> query_model);

signals:
    void signalQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index);

private:
    QPointer<Model::QueryModel> query_model_;
    Ui::TableStylePage *ui;
};

}

}
