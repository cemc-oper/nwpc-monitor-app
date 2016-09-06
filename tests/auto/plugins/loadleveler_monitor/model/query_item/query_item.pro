QT       += testlib
QT       += core gui widgets

TARGET = tst_query_item_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_query_item_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
