
#ifndef __SYMBOID_SDK_ARCH_DEFS_H__
#define __SYMBOID_SDK_ARCH_DEFS_H__

#include "sdk/defs.h"

#ifdef BUILD_SDK_ARCH
    #define SDK_ARCH_API SY_API_EXPORT
#else
    #define SDK_ARCH_API SY_API_IMPORT
#endif

#define arh_ns_begin sy_ns_begin(arh)
#define arh_ns_end sy_ns_end

#endif // __SYMBOID_SDK_ARCH_DEFS_H__
