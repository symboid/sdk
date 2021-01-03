
#ifndef __SYMBOID_SDK_ARCH_APPQT_H__
#define __SYMBOID_SDK_ARCH_APPQT_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/app.h"
#include "sdk/arch/modqt.h"
#include "sdk/arch/mainobject.h"
#include <QGuiApplication>
#include <QString>
#include <QOperatingSystemVersion>

arh_ns_begin

template<>
inline QGuiApplication* main_object_create(int* _argc, char*** _argv)
{
    const QOperatingSystemVersion osVersion(QOperatingSystemVersion::current());
    if (osVersion.type() == QOperatingSystemVersion::Windows && osVersion.majorVersion() < 10)
    {
        QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    }
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
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
        _M_qt_application->setApplicationName(_AppMod::name);
        _M_qt_application->setOrganizationName(_AppMod::company);
        _M_qt_application->setOrganizationDomain(_AppMod::domain);
        _M_mod_main.init_file_log();
    }
    mod_main _M_mod_main;
    main_object_init<qt_application, int*, char***> _M_qt_application;

    int exec() { return _M_qt_application->exec(); }

    QString name() const { return _M_qt_application->applicationName(); }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQT_H__
