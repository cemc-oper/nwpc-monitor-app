include($$PWD/../../../../nwpc-monitor-app.pri)

INCLUDEPATH += $$source_base_dir/src/libs
INCLUDEPATH += $$source_base_dir/src/plugins

LIBS += -L$$build_lib_dir -lplugin_system -lprogress_util -lutil\
        -L$$build_plugins_dir -lcore_plugin \
        -L$$build_plugins_dir/python_env -lpython_env
