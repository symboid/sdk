
#ifndef __SYMBOID_SDK_ARCH_APP_H__
#define __SYMBOID_SDK_ARCH_APP_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/mod.h"
#include "sdk/arch/modmain.h"
#include "sdk/arch/mainobject.h"

arh_ns_begin

template <class _AppMod>
struct app : mod<_AppMod>
{
    mod_main _M_mod_main;
};

arh_ns_end

#define APP_OBJECT(app_name) \
    __MAIN_OBJECT(app_##app_name, app_name, app, true)

#endif // __SYMBOID_SDK_APP_APP_H__
