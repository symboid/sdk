
#ifndef __SYMBOID_SDK_ARCH_APPQT_H__
#define __SYMBOID_SDK_ARCH_APPQT_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/app.h"
#include "sdk/arch/modqt.h"
#include "sdk/arch/mainobject.h"
#include <QGuiApplication>
#include <QString>

arh_ns_begin

template<>
inline QGuiApplication* main_object_create(int* _argc, char*** _argv)
{
    return new QGuiApplication(*_argc, *_argv);
}

struct qt_application
{
    MAIN_OBJECT(QGuiApplication, Application)
};

template <class _AppMod>
struct app_qt : public mod_qt<_AppMod>
{
    app_qt(int* _argc, char*** _argv)
        : _M_qt_application(_argc, _argv)
    {
    }
    mod_main _M_mod_main;
    main_object_init<qt_application, int*, char***> _M_qt_application;

    int exec() { return _M_qt_application->exec(); }

    QString name() const { return _M_qt_application->applicationName(); }
    void setName(const QString& _app_name) { _M_qt_application->setApplicationName(_app_name); }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQT_H__
