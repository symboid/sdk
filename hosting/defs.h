
#ifndef __SYMBOID_SDK_HOSTING_DEFS_H__
#define __SYMBOID_SDK_HOSTING_DEFS_H__

#include "sdk/defs.h"

#ifdef BUILD_SDK_HOSTING
    #define SDK_HOSTING_API SY_API_EXPORT
#else
    #define SDK_HOSTING_API SY_API_IMPORT
#endif

#endif // __SYMBOID_SDK_HOSTING_DEFS_H__
