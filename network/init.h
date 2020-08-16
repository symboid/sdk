
#ifndef __SYMBOID_SDK_NETWORK_INIT_H__
#define __SYMBOID_SDK_NETWORK_INIT_H__

#include "sdk/network/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/network/qrestclient.h"
#include "sdk/network/qrestobjectmodel.h"
#include "sdk/network/qresttablemodel.h"

struct SDK_NETWORK_API mod_sdk_network : arh::mod_qt<mod_sdk_network>
{
    MOD_OBJECT(sdk_network)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Network";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_network();
    ~mod_sdk_network();

    qml_type_register<QRestClient> _reg_rest_client;
    qml_type_register<QRestObjectModel> _reg_rest_object_model;
    qml_type_register<QRestTableModel> _reg_rest_table_model;
};

#endif // __SYMBOID_SDK_NETWORK_INIT_H__
