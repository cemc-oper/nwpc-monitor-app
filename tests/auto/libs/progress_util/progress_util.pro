TEMPLATE = subdirs

SUBDIRS += \
    program_normal \
    program_crash \
    program_nonzero_exitcode \
    program_output

synchronous_job.depends += $$SUBDIRS

SUBDIRS += synchronous_job
