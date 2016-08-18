DEFINES += LOADLEVELER_MONITOR_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = loadleveler_monitor
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system -lutil\
        -L$$build_plugins_dir -lcore_plugin \
        -L$$build_plugins_dir/python_env -lpython_env

DESTDIR = $$build_plugins_dir/loadleveler_monitor

SOURCES += loadleveler_monitor_plugin.cpp \
    loadleveler_monitor_perspective.cpp \
    loadleveler_monitor_widget.cpp \
    loadleveler_client.cpp \
    loadleveler_model/job_query_model.cpp \
    loadleveler_model/job_query_item.cpp \
    client_command_widget.cpp \
    panels/llq_panel.cpp

HEADERS += loadleveler_monitor_plugin.h \
    loadleveler_monitor_global.h \
    loadleveler_monitor_perspective.h \
    loadleveler_monitor_widget.h \
    loadleveler_client.h \
    loadleveler_model/job_query_model.h \
    loadleveler_model/job_query_item.h \
    client_command_widget.h \
    panels/llq_panel.h

DISTFILES += loadleveler_monitor.json \
    nwpc_loadleveler/loadleveler.py

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    loadleveler_monitor_widget.ui \
    client_command_widget.ui \
    panels/llq_panel.ui

RESOURCES += \
    loadleveler_monitor.qrc
