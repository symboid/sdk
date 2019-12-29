
#ifndef __SYMBOID_SDK_NETWORK_QT_DEFS_H__
#define __SYMBOID_SDK_NETWORK_QT_DEFS_H__

#include "sdk/defs.h"

#ifdef BUILD_SDK_NETWORK_QT
    #define SDK_NETWORK_QT_API SY_API_EXPORT
#else
    #define SDK_NETWORK_QT_API SY_API_IMPORT
#endif

#endif // __SYMBOID_SDK_NETWORK_QT_DEFS_H__
