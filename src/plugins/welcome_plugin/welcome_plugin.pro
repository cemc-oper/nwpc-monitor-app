DEFINES += WELCOME_PLUGIN_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = welcome_plugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system \
        -L$$build_plugins_dir -lcore_plugin

DESTDIR = $$build_base_dir/plugins

SOURCES += welcome_plugin.cpp \
    welcome_perspective.cpp \
    welcome_widget.cpp

HEADERS += welcome_plugin.h \
    welcome_plugin_global.h \
    welcome_perspective.h \
    welcome_widget.h

DISTFILES += welcome_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    welcome_widget.ui

RESOURCES += \
    welcome_plugin.qrc
