
#ifndef __SYMBOID_SDK_DOX_QT_INIT_H__
#define __SYMBOID_SDK_DOX_QT_INIT_H__

#include "sdk/dox-qt/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/uicontrols-qt/init.h"
#include "sdk/dox-qt/document.h"

struct SDK_DOX_QT_API mod_sdk_dox_qt : arh::mod_qt<mod_sdk_dox_qt>
{
    MOD_OBJECT(sdk_dox_qt)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Dox";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_dox_qt();
    ~mod_sdk_dox_qt();

    mod_sdk_uicontrols_qt _mod_sdk_uicontrols_qt;

    qml_alias_register<QJsonSyncNode> _reg_json_sync_node;
    qml_type_register<QDocument> _reg_document;
};

#endif // __SYMBOID_SDK_NETWORK_QT_INIT_H__
