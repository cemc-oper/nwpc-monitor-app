#pragma once

#include "../core_plugin_global.h"
#include <QWidget>

namespace Core{

namespace ProgressSystem{

namespace Ui {
class ProgressView;
}

class CORE_PLUGIN_EXPORT ProgressView : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressView(QWidget *parent = 0);
    ~ProgressView();

    void addProgressItemWidget(QWidget *widget);

private:
    Ui::ProgressView *ui;
};

}

}
