
#ifndef __SYMBOID_SDK_HOSTING_INIT_H__
#define __SYMBOID_SDK_HOSTING_INIT_H__

#include "sdk/hosting/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/uicontrols-qt/init.h"
#include "sdk/network/init.h"
#include "sdk/hosting/qconfig.h"
#include "sdk/hosting/qsoftwareconfig.h"
#include "sdk/hosting/qsoftwareupdate.h"

struct SDK_HOSTING_API mod_sdk_hosting : arh::mod_qt<mod_sdk_hosting>
{
    MOD_OBJECT(sdk_hosting)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Hosting";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_hosting();
    ~mod_sdk_hosting();

    arh::mod_init<mod_sdk_uicontrols_qt> _M_mod_sdk_uicontrols_qt;
    arh::mod_init<mod_sdk_network> _M_mod_sdk_network;

    qml_type_register<QConfigNode> _reg_config_node;
    qml_singleton_init<QSoftwareConfig> _reg_software_config;
    qml_type_register<QSoftwareVersion> _reg_software_version;
    qml_singleton_init<QSoftwareUpdate> _reg_software_update;
};

#endif // __SYMBOID_SDK_HOSTING_INIT_H__
