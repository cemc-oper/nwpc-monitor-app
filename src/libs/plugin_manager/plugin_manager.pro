#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T17:28:47
#
#-------------------------------------------------

include(../../../nwpc-monitor-app.pri)

QT       -= gui

TARGET = plugin_manager
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$build_base_dir/bin

SOURCES += plugin_manager.cpp

HEADERS += plugin_manager.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
