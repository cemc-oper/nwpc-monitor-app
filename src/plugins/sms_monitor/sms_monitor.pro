DEFINES += SMS_MONITOR_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = sms_monitor
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system -lutil \
        -L$$build_plugins_dir -lcore_plugin \
        -L$$build_plugins_dir/python_env -lpython_env

DESTDIR = $$build_plugins_dir/sms_monitor

SOURCES += sms_monitor_plugin.cpp \
    sms_monitor_perspective.cpp \
    sms_monitor_widget.cpp \
    sms_monitor_client.cpp \
    sms_model/node.cpp \
    sms_model/bunch.cpp

HEADERS += sms_monitor_plugin.h \
    sms_monitor_global.h \
    sms_monitor_perspective.h \
    sms_monitor_widget.h \
    sms_monitor_client.h \
    sms_model/node.h \
    sms_model/bunch.h

DISTFILES += sms_monitor.json \
    nwpc_sms_monitor/update_sms_status.py

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    sms_monitor_widget.ui
