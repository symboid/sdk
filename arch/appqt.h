
#ifndef __SYMBOID_SDK_ARCH_APPQT_H__
#define __SYMBOID_SDK_ARCH_APPQT_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/app.h"
#include "sdk/arch/mainobject.h"

arh_ns_begin

template <class _AppMod, class _QtApplication>
struct app_qt : public app<_AppMod>
{
    app_qt(int* _argc, char*** _argv)
        : _M_qt_application(_argc, _argv)
    {
    }
    main_object_init<_QtApplication, int*, char***> _M_qt_application;

    int exec() { return _M_qt_application->exec(); }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQT_H__
