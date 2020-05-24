
#ifndef __SYMBOID_SDK_HOSTING_INIT_H__
#define __SYMBOID_SDK_HOSTING_INIT_H__

#include "sdk/hosting/defs.h"
#include "sdk/arch/modqt.h"

struct SDK_HOSTING_API mod_sdk_hosting : arh::mod_qt<mod_sdk_hosting>
{
    MOD_OBJECT(sdk_hosting)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Hosting";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_hosting();
    ~mod_sdk_hosting();
};


#endif // __SYMBOID_SDK_HOSTING_INIT_H__
