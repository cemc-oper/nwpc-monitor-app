#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T17:31:13
#
#-------------------------------------------------

DEFINES += CORE_PLUGIN_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = core_plugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH+=../../libs

LIBS += -L$$build_lib_dir -lplugin_system

DESTDIR = $$base_build_dir/bin

SOURCES += core_plugin.cpp \
    mainwindow.cpp

HEADERS += core_plugin.h \
    core_plugin_global.h \
    mainwindow.h

DISTFILES += core_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    mainwindow.ui
