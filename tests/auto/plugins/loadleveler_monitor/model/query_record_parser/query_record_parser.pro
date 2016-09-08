QT       += widgets testlib

TARGET = tst_query_record_parser_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../loadleveler_monitor_test.pri)

SOURCES += tst_query_record_parser_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

DISTFILES += \
    data/detail_query/llclass/minijob.txt \
    data/detail_query/llclass/normal1.txt \
    data/detail_query/llclass/operation.txt \
    data/detail_query/llclass/operation1.txt \
    data/detail_query/llclass/serial_op.txt \
    data/detail_query/llq/parallel_job_idle.txt \
    data/detail_query/llq/parallel_job_running.txt \
    data/detail_query/llq/parallel_multi_step_job_idle.txt \
    data/detail_query/llq/parallel_multi_step_job_running.txt \
    data/detail_query/llq/serial_job_running.txt
