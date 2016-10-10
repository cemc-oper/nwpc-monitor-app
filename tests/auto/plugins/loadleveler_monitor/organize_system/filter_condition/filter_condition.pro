QT       += testlib

TARGET = tst_filter_condition_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_filter_condition_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
