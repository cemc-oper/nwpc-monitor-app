QT       += widgets testlib

TARGET = tst_query_item_value_saver_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_query_item_value_saver_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
