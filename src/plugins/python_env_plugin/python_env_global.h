#pragma once

#if defined(PYTHON_ENV_LIBRARY)
#  define PYTHON_ENV_EXPORT Q_DECL_EXPORT
#else
#  define PYTHON_ENV_EXPORT Q_DECL_IMPORT
#endif
