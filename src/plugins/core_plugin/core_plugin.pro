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
    actionmanager/action_manager.cpp \
    actionmanager/action_container.cpp \
    actionmanager/menu_action_container.cpp \
    actionmanager/menu_bar_action_container.cpp

HEADERS += core_plugin.h \
    core_plugin_global.h \
    mainwindow.h \
    iperspective.h \
    actionmanager/action_manager.h \
    actionmanager/action_container.h \
    actionmanager/menu_action_container.h \
    actionmanager/menu_bar_action_container.h

DISTFILES += core_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    mainwindow.ui
