QT       += testlib

QT       -= gui

TARGET = tst_session_managertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../core_plugin.pri)

SOURCES += tst_session_managertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
