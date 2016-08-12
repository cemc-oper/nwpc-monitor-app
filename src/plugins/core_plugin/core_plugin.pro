DEFINES += CORE_PLUGIN_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = core_plugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH+=../../libs

LIBS += -L$$build_lib_dir -lplugin_system

DESTDIR = $$build_base_dir/plugins

SOURCES += core_plugin.cpp \
    mainwindow.cpp \
    iperspective.cpp \
    action_manager/action_manager.cpp \
    action_manager/action_container.cpp \
    action_manager/menu_action_container.cpp \
    action_manager/menu_bar_action_container.cpp \
    action_manager/action.cpp

HEADERS += core_plugin.h \
    core_plugin_global.h \
    mainwindow.h \
    iperspective.h \
    action_manager/action_manager.h \
    action_manager/action_container.h \
    action_manager/menu_action_container.h \
    action_manager/menu_bar_action_container.h \
    action_manager/action.h \
    core_plugin_constants.h

DISTFILES += core_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    mainwindow.ui
