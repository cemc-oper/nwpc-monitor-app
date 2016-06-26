#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T17:28:47
#
#-------------------------------------------------
DEFINES += PLUGIN_SYSTEM_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       -= gui

TARGET = plugin_system
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$build_lib_dir

SOURCES += plugin_manager.cpp \
    iplugin.cpp

HEADERS += plugin_manager.h \
    iplugin.h \
    plugin_system_global.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
