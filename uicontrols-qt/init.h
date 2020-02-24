
#ifndef __SYMBOID_SDK_UICONTROLS_QT_INIT_H__
#define __SYMBOID_SDK_UICONTROLS_QT_INIT_H__

#include "sdk/uicontrols-qt/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/uicontrols-qt/qinputoperation.h"
#include "sdk/uicontrols-qt/qunixtimeconverter.h"

struct SDK_UICONTROLS_QT_API mod_sdk_uicontrols_qt : arh::mod_qt<mod_sdk_uicontrols_qt>
{
    MOD_OBJECT(sdk_uicontrols_qt)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Controls";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_uicontrols_qt();
    ~mod_sdk_uicontrols_qt();

    qml_type_register<QInputOperation> _reg_input_item_object;
    qml_type_register<QInputOperationsItem> _reg_input_operations;
    qml_type_register<QUnixTimeConverter> _reg_unix_time_converter;
};


#endif // __SYMBOID_SDK_UICONTROLS_QT_INIT_H__
