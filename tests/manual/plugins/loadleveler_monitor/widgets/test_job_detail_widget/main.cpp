#include "test_job_detail_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestJobDetailWidget w;
    w.show();

    return a.exec();
}
