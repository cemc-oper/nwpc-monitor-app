#pragma once

#include <QWidget>

namespace LoadLevelerMonitor{

namespace Panels{

namespace Ui {
class LlqPanel;
}

class LlqPanel : public QWidget
{
    Q_OBJECT

public:
    explicit LlqPanel(QWidget *parent = 0);
    ~LlqPanel();

private:
    Ui::LlqPanel *ui;
};

}

}
