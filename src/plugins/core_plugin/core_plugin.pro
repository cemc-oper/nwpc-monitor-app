DEFINES += CORE_PLUGIN_LIBRARY

include(../../../nwpc-monitor-app.pri)

QT       += core gui widgets

TARGET = core_plugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH+=../../libs
INCLUDEPATH += ../../plugins

LIBS += -L$$build_lib_dir -lplugin_system

DESTDIR = $$build_base_dir/plugins

SOURCES += core_plugin.cpp \
    mainwindow.cpp \
    action_system/action_manager.cpp \
    action_system/action_container.cpp \
    action_system/menu_action_container.cpp \
    action_system/menu_bar_action_container.cpp \
    action_system/action.cpp \
    view_system/view_manager.cpp \
    view_system/view_spec.cpp \
    view_system/iview.cpp \
    view_system/dock_view.cpp \
    view_system/view_manager_private.cpp \
    view_system/dock_widget.cpp \
    action_system/group_action_container.cpp \
    perspective_system/iperspective.cpp \
    perspective_system/perspective_manager.cpp \
    perspective_system/perspective_manager_private.cpp \
    views/console_dock_widget.cpp \
    progress_system/progress_manager.cpp \
    progress_system/progress_manager_private.cpp \
    progress_system/progress_view.cpp \
    progress_system/progress_item_widget.cpp \
    views/progress_dock_widget.cpp \
    progress_system/progress_status_bar_widget.cpp \
    session_system/session.cpp \
    session_system/session_manager.cpp \
    session_system/session_widget.cpp \
    session_system/session_setting_dialog.cpp

HEADERS += core_plugin.h \
    core_plugin_global.h \
    mainwindow.h \
    action_system/action_manager.h \
    action_system/action_container.h \
    action_system/menu_action_container.h \
    action_system/action.h \
    core_plugin_constants.h \
    view_system/view_manager.h \
    view_system/view_spec.h \
    view_system/iview.h \
    view_system/dock_view.h \
    view_system/view_manager_private.h \
    view_system/dock_widget.h \
    action_system/group_action_container.h \
    action_system/menu_bar_action_container.h \
    perspective_system/iperspective.h \
    perspective_system/perspective_manager.h \
    perspective_system/perspective_manager_private.h \
    views/console_dock_widget.h \
    progress_system/progress_manager.h \
    progress_system/progress_manager_private.h \
    progress_system/progress_view.h \
    progress_system/progress_item_widget.h \
    views/progress_dock_widget.h \
    progress_system/progress_status_bar_widget.h \
    session_system/session.h \
    session_system/session_manager.h \
    session_system/session_widget.h \
    session_system/session_setting_dialog.h

DISTFILES += core_plugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    mainwindow.ui \
    views/console_dock_widget.ui \
    progress_system/progress_view.ui \
    progress_system/progress_item_widget.ui \
    views/progress_dock_widget.ui \
    progress_system/progress_status_bar_widget.ui \
    session_system/session_widget.ui \
    session_system/session_setting_dialog.ui

RESOURCES += \
    core.qrc
