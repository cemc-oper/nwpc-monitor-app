DEFINES += LOADLEVELER_MONITOR_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets charts

TARGET = loadleveler_monitor
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system -lprogress_util\
        -L$$build_plugins_dir -lcore_plugin \
        -L$$build_plugins_dir/python_env -lpython_env

DESTDIR = $$build_plugins_dir/loadleveler_monitor

SOURCES += loadleveler_monitor_plugin.cpp \
    loadleveler_monitor_perspective.cpp \
    loadleveler_monitor_widget.cpp \
    loadleveler_client.cpp \
    client_command_widget.cpp \
    panels/llq_panel.cpp \
    model/llq_command_manager.cpp \
    model/llq_command_manager_private.cpp \
    model/query_category.cpp \
    model/query_item.cpp \
    model/query_model.cpp \
    model/query_category_list.cpp \
    chart/processor_condition.cpp \
    chart/model_processor.cpp \
    chart/model_category_processor.cpp

HEADERS += loadleveler_monitor_plugin.h \
    loadleveler_monitor_global.h \
    loadleveler_monitor_perspective.h \
    loadleveler_monitor_widget.h \
    loadleveler_client.h \
    client_command_widget.h \
    panels/llq_panel.h \
    model/llq_command_manager.h \
    model/llq_command_manager_private.h \
    model/query_category.h \
    model/query_item.h \
    model/query_model.h \
    model/query_category_list.h \
    chart/processor_condition.h \
    chart/model_processor.h \
    chart/model_category_processor.h

DISTFILES += loadleveler_monitor.json \
    nwpc_loadleveler/loadleveler.py

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    loadleveler_monitor_widget.ui \
    client_command_widget.ui \
    panels/llq_panel.ui

RESOURCES += \
    loadleveler_monitor.qrc
