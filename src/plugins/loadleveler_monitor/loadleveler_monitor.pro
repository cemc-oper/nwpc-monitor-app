DEFINES += LOADLEVELER_MONITOR_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = loadleveler_monitor
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system \
        -L$$build_plugins_dir -lcore_plugin

DESTDIR = $$build_plugins_dir

SOURCES += loadleveler_monitor_plugin.cpp \
    loadleveler_monitor_perspective.cpp \
    loadleveler_monitor_widget.cpp

HEADERS += loadleveler_monitor_plugin.h \
    loadleveler_monitor_global.h \
    loadleveler_monitor_perspective.h \
    loadleveler_monitor_widget.h

DISTFILES += loadleveler_monitor.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    loadleveler_monitor_widget.ui
