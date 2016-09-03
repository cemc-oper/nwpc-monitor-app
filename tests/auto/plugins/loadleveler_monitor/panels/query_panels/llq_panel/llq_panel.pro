QT       += widgets testlib

TARGET = tst_llq_paneltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../../../../../../nwpc-monitor-app.pri)

INCLUDEPATH += $$source_base_dir/src/libs
INCLUDEPATH += $$source_base_dir/src/plugins

LIBS += -L$$build_lib_dir -lplugin_system -lprogress_util -lutil\
        -L$$build_plugins_dir -lcore_plugin \
        -L$$build_plugins_dir/python_env -lpython_env
LIBS += -L$$build_plugins_dir/loadleveler_monitor -lloadleveler_monitor

SOURCES += \
    tst_llq_panel_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
