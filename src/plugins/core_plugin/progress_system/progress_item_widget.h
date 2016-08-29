#pragma once

#include <QWidget>

namespace Core {

namespace ProgressSystem{

namespace Ui {
class ProgressItemWidget;
}

class ProgressItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressItemWidget(QWidget *parent = 0);
    ~ProgressItemWidget();

    void setTitle(const QString &title);
    void setDescription(const QString &description);
    void setProgressValue(int value);

    int getProgressMaxValue() const;

private:
    Ui::ProgressItemWidget *ui;
};

}

}
