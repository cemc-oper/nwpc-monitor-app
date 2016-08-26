#include "text_style_page.h"
#include "ui_text_style_page.h"

using namespace LoadLevelerMonitor::Panels;

TextStylePage::TextStylePage(QWidget *parent) :
    StylePage{parent},
    ui(new Ui::TextStylePage)
{
    ui->setupUi(this);
}

TextStylePage::~TextStylePage()
{
    delete ui;
}

void TextStylePage::clear()
{
    ui->text_view->clear();
}

void TextStylePage::setText(const QString &text)
{
    ui->text_view->setText(text);
}
