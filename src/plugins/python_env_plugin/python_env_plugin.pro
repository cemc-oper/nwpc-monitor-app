DEFINES += PYTHON_ENV_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui

TARGET = python_env
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system -lprogress_util \
        -L$$build_lib_dir -lutil \
        -L$$build_plugins_dir -lcore_plugin

DESTDIR = $$build_plugins_dir/python_env

SOURCES += python_env_plugin.cpp \
    python_engine.cpp \
    python_command.cpp

HEADERS += python_env_plugin.h \
    python_env_global.h \
    python_engine.h \
    python_command.h

DISTFILES += python_env_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
