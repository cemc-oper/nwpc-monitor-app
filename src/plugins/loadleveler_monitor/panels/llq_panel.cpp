#include "llq_panel.h"
#include "ui_llq_panel.h"

using namespace LoadLevelerMonitor::Panels;

LlqPanel::LlqPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LlqPanel)
{
    ui->setupUi(this);
}

LlqPanel::~LlqPanel()
{
    delete ui;
}
