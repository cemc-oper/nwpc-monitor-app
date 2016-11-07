QT       += core gui widgets testlib

include(../../loadleveler_monitor.pri)

TARGET = test_job_detail_widget
TEMPLATE = app


SOURCES += main.cpp\
        test_job_detail_widget.cpp

HEADERS  += test_job_detail_widget.h

FORMS    += test_job_detail_widget.ui

DISTFILES += \
    data/serial_running_job_detail.txt \
    data/parallel_idle_job_detail.txt \
    data/serial_idle_job_detail.txt \
    data/parallel_running_job_detail.txt
