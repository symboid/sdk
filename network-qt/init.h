
#ifndef __SYMBOID_SDK_NETWORK_QT_INIT_H__
#define __SYMBOID_SDK_NETWORK_QT_INIT_H__

#include "sdk/network-qt/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/network-qt/qresttablemodel.h"

struct mod_sdk_network_qt : arh::mod_qt<mod_sdk_network_qt>
{
    MOD_OBJECT(sdk_network_qt)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Network";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_network_qt();
    ~mod_sdk_network_qt();

    qml_type_register<QRestTableModel> _reg_rest_table_model;
    qml_type_register<QRestObjectModel> _reg_object_table_model;
};


#endif // __SYMBOID_SDK_NETWORK_QT_INIT_H__
