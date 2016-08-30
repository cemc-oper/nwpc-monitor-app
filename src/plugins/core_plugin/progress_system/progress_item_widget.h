#pragma once

#include "../core_plugin_global.h"
#include <QWidget>

namespace Core {

namespace ProgressSystem{

namespace Ui {
class ProgressItemWidget;
}

class CORE_PLUGIN_EXPORT ProgressItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressItemWidget(QWidget *parent = 0);
    ~ProgressItemWidget();

    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setProgressValue(int value);

    int getProgressMaxValue() const;

    bool isProgressFinished() const;

private:
    Ui::ProgressItemWidget *ui;
};

}

}
