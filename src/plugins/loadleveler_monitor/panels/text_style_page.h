#pragma once

#include "style_page.h"

namespace LoadLevelerMonitor{

namespace Panels{

namespace Ui {
class TextStylePage;
}

class TextStylePage : public StylePage
{
    Q_OBJECT

public:
    explicit TextStylePage(QWidget *parent = 0);
    ~TextStylePage();

    void clear();
    void setText(const QString &text);

private:
    Ui::TextStylePage *ui;
};

}

}
