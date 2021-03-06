
#ifndef __SYMBOID_SDK_ARCH_MODMAIN_H__
#define __SYMBOID_SDK_ARCH_MODMAIN_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/mod.h"
#include "sdk/arch/log.h"

arh_ns_begin

struct SDK_ARCH_API mod_main : basic_mod
{
    mod_main(const char* company_name, const char* app_name);
    ~mod_main();
#if SY_PLATFORM_IS_ANDROID
    android_log _M_default_log;
#else
    console_log _M_default_log;
#endif
    file_log* _M_file_log;
    void init_file_log();
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_MODMAIN_H__
