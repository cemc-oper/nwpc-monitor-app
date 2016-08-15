#include "output_dock_widget.h"
#include "ui_output_dock_widget.h"

using namespace Core::Views;

OutputDockWidget::OutputDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::OutputDockWidget)
{
    ui->setupUi(this);

    connect(ui->warp_line_button, &QPushButton::toggled, [=](bool flag){
        if(flag)
            ui->output_text->setLineWrapMode(QTextEdit::WidgetWidth);
        else
            ui->output_text->setLineWrapMode(QTextEdit::NoWrap);
    });
}

OutputDockWidget::~OutputDockWidget()
{
    delete ui;
}
