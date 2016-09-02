QT       += widgets testlib

TARGET = tst_model_view_util_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../../../../nwpc-monitor-app.pri)

INCLUDEPATH += $$source_base_dir/src/libs
INCLUDEPATH += $$source_base_dir/src/plugins

LIBS += -L$$build_lib_dir -lutil

SOURCES += tst_model_view_util_test.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
