QT       += widgets testlib

TARGET = tst_session_system_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../core_plugin.pri)

SOURCES += tst_session_system_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
