
#ifndef __SYMBOID_SDK_ARCH_APPQML_H__
#define __SYMBOID_SDK_ARCH_APPQML_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/appqt.h"
#include "sdk/arch/mainobject.h"
#include <QQmlApplicationEngine>

arh_ns_begin

struct qml_engine
{
    MAIN_OBJECT(QQmlApplicationEngine, QmlEngine)
};

template <class _AppMod>
struct app_qml : app_qt<_AppMod>
{
    app_qml(int* _argc, char*** _argv)
        : app_qt<_AppMod>(_argc, _argv)
        , _M_main_qml("qrc:///main.qml")
    {
        _M_qml_engine->addImportPath("qrc:///");
    }
    main_object_init<qml_engine> _M_qml_engine;
    QUrl _M_main_qml;
    int run()
    {
        _M_qml_engine->load(_M_main_qml);
        return app_qt<_AppMod>::exec();
    }
};

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_APPQML_H__
