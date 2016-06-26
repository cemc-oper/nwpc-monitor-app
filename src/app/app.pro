include(../../nwpc-monitor-app.pri)

TEMPLATE = app

QT += widgets

TARGET = nwpc-monitor-app
DESTDIR=$$build_base_dir/bin

SOURCES += \
    main.cpp
