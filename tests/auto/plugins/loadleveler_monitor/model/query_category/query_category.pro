QT       += widgets testlib

TARGET = tst_query_category_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_query_category_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
