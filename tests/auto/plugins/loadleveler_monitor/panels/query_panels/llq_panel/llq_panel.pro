QT       += widgets testlib

TARGET = tst_llq_paneltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


include(../../../loadleveler_monitor_test.pri)

SOURCES += \
    tst_llq_panel_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
