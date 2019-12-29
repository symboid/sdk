
#ifndef __SYMBOID_SDK_ARCH_APPQML_H__
#define __SYMBOID_SDK_ARCH_APPQML_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/appqt.h"
#include "sdk/arch/mainobject.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

arh_ns_begin

template<>
QGuiApplication* main_object_create(int* _argc, char*** _argv)
{
    return new QGuiApplication(*_argc, *_argv);
}

struct gui_application
{
    MAIN_OBJECT(QGuiApplication, Application)
};

struct qml_engine
{
    MAIN_OBJECT(QQmlApplicationEngine, QmlEngine)
};

template <class _AppMod>
struct app_qml : app_qt<_AppMod, gui_application>
{
    app_qml(int* _argc, char*** _argv)
        : app_qt<_AppMod, gui_application>(_argc, _argv)
    {
        _M_qml_engine->addImportPath("qrc:///");
    }
    main_object_init<qml_engine> _M_qml_engine;
    int run(const char* _main_qml_path)
    {
        _M_qml_engine->load(QUrl(_main_qml_path));
        return app_qt<_AppMod, gui_application>::exec();
    }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQML_H__
