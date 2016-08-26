#include "model_view_util.h"

#include <QStandardItem>
#include <QStandardItemModel>

using namespace Util::ModelView;

namespace Util{

namespace ModelView{

UTILSHARED_EXPORT void changeAllItemsCheckState(QStandardItemModel *model, Qt::CheckState check_state)
{
    QStandardItem * root_item = model->invisibleRootItem();
    int row_count = root_item->rowCount();
    for(int i=0; i<row_count; i++)
    {
        root_item->child(i, 0)->setCheckState(check_state);
    }
}

}

}
