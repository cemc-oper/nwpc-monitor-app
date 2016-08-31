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

    int getProgressMaxValue() const;
    bool isProgressFinished() const;

public slots:
    void slotProgressFinish();
    void setProgressValue(int value);

private:
    void setProgressIcon(const QString &icon_location);
    Ui::ProgressItemWidget *ui;
};

}

}
