include(../../nwpc-monitor-app.pri)

TEMPLATE = app

QT += widgets

TARGET = nwpc-monitor-app
DESTDIR=$$build_base_dir/bin

INCLUDEPATH += ../libs

LIBS += -L$$build_lib_dir -lplugin_system

SOURCES += \
    main.cpp

RC_ICONS = logo.ico
