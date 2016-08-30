#pragma once

#include "../view_system/dock_widget.h"

#include <QDockWidget>

namespace Core{

namespace ViewSystem{
class DockWidget;
}

namespace ProgressSystem{
class ProgressView;
}

namespace Views{

namespace Ui {
class ProgressDockWidget;
}

class ProgressDockWidget : public ViewSystem::DockWidget
{
    Q_OBJECT

public:
    explicit ProgressDockWidget(QWidget *parent = 0);
    ~ProgressDockWidget();

    ProgressSystem::ProgressView *progressView();

private:
    Ui::ProgressDockWidget *ui;
};

}

}
