DEFINES += PLUGIN_SYSTEM_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += widgets

TARGET = plugin_system
TEMPLATE = lib
CONFIG += shared dll

win32{
    DESTDIR = $$build_base_dir/lib
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}


SOURCES += plugin_manager.cpp \
    iplugin.cpp \
    plugin_spec.cpp \
    plugin_manager_private.cpp

HEADERS += plugin_manager.h \
    iplugin.h \
    plugin_system_global.h \
    plugin_spec.h \
    plugin_manager_private.h
