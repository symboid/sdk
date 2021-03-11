
#ifndef __SYMBOID_SDK_CONTROLS_DEFS_H__
#define __SYMBOID_SDK_CONTROLS_DEFS_H__

#include "sdk/arch/defs.h"

#ifdef BUILD_SDK_CONTROLS
    #define SDK_CONTROLS_API SY_API_EXPORT
#else
    #define SDK_CONTROLS_API SY_API_IMPORT
#endif

#endif // __SYMBOID_SDK_CONTROLS_DEFS_H__
