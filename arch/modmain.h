
#ifndef __SYMBOID_SDK_ARCH_MODMAIN_H__
#define __SYMBOID_SDK_ARCH_MODMAIN_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/mod.h"
#include "sdk/arch/log.h"

arh_ns_begin

struct mod_main : basic_mod
{
    mod_main();
    ~mod_main();
    console_log _M_console_log;
    file_log _M_file_log;
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_MODMAIN_H__
