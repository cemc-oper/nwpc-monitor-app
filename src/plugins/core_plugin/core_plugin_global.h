#pragma once

#if defined(CORE_PLUGIN_LIBRARY)
#  define CORE_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define CORE_PLUGIN_EXPORT Q_DECL_IMPORT
#endif
