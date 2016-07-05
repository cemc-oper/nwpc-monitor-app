#pragma once

#if defined(SMS_MONITOR_LIBRARY)
#  define SMS_MONITOR_EXPORT Q_DECL_EXPORT
#else
#  define SMS_MONITOR_EXPORT Q_DECL_IMPORT
#endif
