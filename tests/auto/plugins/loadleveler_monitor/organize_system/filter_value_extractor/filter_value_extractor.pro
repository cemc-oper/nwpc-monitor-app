QT       += widgets testlib

TARGET = tst_filter_value_extractor_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_filter_value_extractor_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
