QT       += testlib

QT       -= gui

TARGET = tst_query_util_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_query_util_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
