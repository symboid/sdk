
#ifndef __SYMBOID_SDK_UICONTROLS_QT_INIT_H__
#define __SYMBOID_SDK_UICONTROLS_QT_INIT_H__

#include "sdk/uicontrols-qt/defs.h"
#include "sdk/arch/modqt.h"

struct SDK_UICONTROLS_QT_API mod_sdk_uicontrols_qt : arh::mod_qt<mod_sdk_uicontrols_qt>
{
    MOD_OBJECT(sdk_uicontrols_qt)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Controls";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_uicontrols_qt();
    ~mod_sdk_uicontrols_qt();
};


#endif // __SYMBOID_SDK_UICONTROLS_QT_INIT_H__
