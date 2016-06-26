#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T17:31:13
#
#-------------------------------------------------

include(../../../nwpc-monitor-app.pri)

QT       += core gui

TARGET = core_plugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH+=../../libs

LIBS += -L$$build_lib_dir -lplugin_system

DESTDIR = $$base_build_dir/bin

SOURCES += core_plugin.cpp

HEADERS += core_plugin.h

DISTFILES += core_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
