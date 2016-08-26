#pragma once

#include "util_global.h"
#include <qnamespace.h>

QT_BEGIN_NAMESPACE
class QStandardItemModel;
QT_END_NAMESPACE

namespace Util{

namespace ModelView{

UTILSHARED_EXPORT void changeAllItemsCheckState(QStandardItemModel *model, Qt::CheckState check_state);

}

}
