include(../../loadleveler_monitor.pri)

QT       += core gui widgets testlib

TARGET = test_filter
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

DISTFILES += \
    data/response.json \
    data/llq_output.txt
