
#ifndef __SYMBOID_SDK_ARCH_MOD_H__
#define __SYMBOID_SDK_ARCH_MOD_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/mainobject.h"
#include <string>

arh_ns_begin

struct SDK_ARCH_API basic_mod
{
    basic_mod(const char* _mod_name);
    ~basic_mod();

    const std::string name;
};

template <class _Mod>
struct mod : basic_mod
{
    mod() : basic_mod(_Mod::id) {}
};

template <class _ModTraits, class... _CtorArgs>
using mod_init = main_object_init<_ModTraits,_CtorArgs...>;

arh_ns_end

#define MOD_OBJECT(module_name) \
    __MAIN_OBJECT(mod_##module_name, module_name, module, true)

#endif // __SYMBOID_SDK_APP_MOD_H__
