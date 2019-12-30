
#ifndef __SYMBOID_SDK_ARCH_APPQTW_H__
#define __SYMBOID_SDK_ARCH_APPQTW_H__

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

struct qtw_application
{
    MAIN_OBJECT(QApplication, Application)
};

template <class _AppMod, class _MainWindow>
struct app_qtw : app_qt<_AppMod, qtw_application>
{
    app_qtw(int* _argc, char*** _argv)
        : app_qt<_AppMod, qtw_application>(_argc, _argv)
    {
    }
    arh::main_object_init<_MainWindow> _M_main_window;
    int run()
    {
        _M_main_window->show();
        return app_qt<_AppMod, qtw_application>::exec();
    }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQTW_H__
