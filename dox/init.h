
#ifndef __SYMBOID_SDK_DOX_INIT_H__
#define __SYMBOID_SDK_DOX_INIT_H__

#include "sdk/dox/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/uicontrols-qt/init.h"
#include "sdk/dox/document.h"
#include "sdk/dox/qdocumentfoldermodel.h"
#include "sdk/dox/qrecentdoxmodel.h"

struct SDK_DOX_API mod_sdk_dox : arh::mod_qt<mod_sdk_dox>
{
    MOD_OBJECT(sdk_dox)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Dox";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_dox();
    ~mod_sdk_dox();

    arh::mod_init<mod_sdk_uicontrols_qt> _mod_sdk_uicontrols_qt;

    qml_alias_register<QJsonSyncNode> _reg_json_sync_node;
    qml_type_register<QDocument> _reg_document;
    qml_type_register<QDocumentFolderModel> _reg_document_folder_model;
    qml_type_register<QRecentDoxModel> _reg_recent_dox_model;
};

#endif // __SYMBOID_SDK_DOX_INIT_H__
