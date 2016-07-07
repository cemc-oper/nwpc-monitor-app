#pragma once

#include <QtCore/qglobal.h>

#if defined(UTIL_LIBRARY)
#  define UTILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UTILSHARED_EXPORT Q_DECL_IMPORT
#endif
