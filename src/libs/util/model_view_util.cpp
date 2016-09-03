#include "model_view_util.h"

#include <QStandardItem>
#include <QStandardItemModel>

#include <QtDebug>

using namespace Util::ModelView;

namespace Util{

namespace ModelView{

UTILSHARED_EXPORT void changeAllItemsCheckState(QStandardItemModel *model, Qt::CheckState check_state)
{
    if(model == nullptr)
        return;
    QStandardItem * root_item = model->invisibleRootItem();
    int row_count = root_item->rowCount();
    for(int i=0; i<row_count; i++)
    {
        root_item->child(i, 0)->setCheckState(check_state);
    }
}

UTILSHARED_EXPORT QList<int> getCheckedRows(QStandardItemModel *model)
{
    QList<int> rows;
    int row_count = model->rowCount();
    for( int i=0; i < row_count; i++)
    {
        if(model->invisibleRootItem()->child(i)->checkState() == Qt::Checked)
            rows<<i;
    }
    return rows;
}

}

}
