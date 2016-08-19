DEFINES += UTIL_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       -= gui

TARGET = util
TEMPLATE = lib
CONFIG += shared dll

INCLUDEPATH += ..

win32{
    DESTDIR = $$build_base_dir/lib
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}


SOURCES += \
    shell_command_util.cpp

HEADERS +=\
        util_global.h \
    shell_command_util.h

