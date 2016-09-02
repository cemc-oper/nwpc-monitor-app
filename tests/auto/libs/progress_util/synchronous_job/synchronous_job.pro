QT       += testlib

QT       += core gui widgets

TARGET = tst_synchronous_job_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../../../../nwpc-monitor-app.pri)

INCLUDEPATH += $$source_base_dir/src/libs
INCLUDEPATH += $$source_base_dir/src/plugins

LIBS += -L$$build_lib_dir -lprogress_util


SOURCES += tst_synchronous_job_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

