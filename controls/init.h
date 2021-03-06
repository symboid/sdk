
#ifndef __SYMBOID_SDK_CONTROLS_INIT_H__
#define __SYMBOID_SDK_CONTROLS_INIT_H__

#include "sdk/controls/defs.h"
#include "sdk/arch/modqt.h"
#include "sdk/controls/qunixtimeconverter.h"
#include "sdk/controls/qcalctask.h"

struct SDK_CONTROLS_API mod_sdk_controls : arh::mod_qt<mod_sdk_controls>
{
    MOD_OBJECT(sdk_controls)

    static constexpr const char* qml_pkg_name = "Symboid.Sdk.Controls";
    static constexpr int qml_pkg_ver_major = 1;
    static constexpr int qml_pkg_ver_minor = 0;

    mod_sdk_controls();
    ~mod_sdk_controls();

    qml_type_register<QUnixTimeConverter> _reg_unix_time_converter;
    qml_type_register<QCalcTask> _reg_calc_task;
    qml_domain_register<QCalcable> _reg_calcable;
};


#endif // __SYMBOID_SDK_CONTROLS_INIT_H__
