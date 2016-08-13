#include "output_dock_widget.h"
#include "ui_output_dock_widget.h"

using namespace Core::Views;

OutputDockWidget::OutputDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::OutputDockWidget)
{
    ui->setupUi(this);
}

OutputDockWidget::~OutputDockWidget()
{
    delete ui;
}
