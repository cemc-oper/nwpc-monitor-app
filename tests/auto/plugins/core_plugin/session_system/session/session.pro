QT       += testlib

TARGET = tst_session_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../core_plugin.pri)

SOURCES += \
    tst_session_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

DISTFILES += \
    data/single_session.json
