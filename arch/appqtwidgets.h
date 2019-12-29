
#ifndef __SYMBOID_SDK_ARCH_APPQTWIDGETS_H__
#define __SYMBOID_SDK_ARCH_APPQTWIDGETS_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/appqt.h"
#include "sdk/arch/mainobject.h"
#include <QApplication>

arh_ns_begin

template<>
QApplication* main_object_create(int* _argc, char*** _argv)
{
    return new QApplication(*_argc, *_argv);
}

template <class _AppMod>
struct app_qt_widgets : app_qt<_AppMod, QApplication>
{
    app_qt_widgets(int* _argc, char*** _argv)
        : app_qt<_AppMod, QApplication>(_argc, _argv)
    {
    }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQTWIDGETS_H__
