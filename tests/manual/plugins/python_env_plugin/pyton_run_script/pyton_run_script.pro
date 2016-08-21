include(../../../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = pyton_run_script
TEMPLATE = app

INCLUDEPATH += $$source_base_dir/src/libs
INCLUDEPATH += $$source_base_dir/src/plugins

LIBS += -L$$build_lib_dir -lplugin_system -lprogress_util \
        -L$$build_plugins_dir -lcore_plugin \
        -L$$build_plugins_dir/python_env -lpython_env \
        -L$$build_plugins_dir/loadleveler_monitor -lloadleveler_monitor


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

DISTFILES += \
    helloworld.py
