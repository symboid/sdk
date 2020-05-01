
#ifndef __SYMBOID_SDK_ARCH_MODQT_H__
#define __SYMBOID_SDK_ARCH_MODQT_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/mod.h"
#include "sdk/arch/mainobject.h"
#include <QQmlEngine>
#include <QTranslator>

namespace std {

template<class _CharT, class _Traits>
basic_ostream<_CharT, _Traits>& operator<<(basic_ostream<_CharT, _Traits>& _os, const QString& _q_string)
{
    return _os << _q_string.toUtf8().data();
}

} // namespace std

arh_ns_begin

class SDK_ARCH_API basic_qt_translation
{
    QTranslator _M_qm_file;
protected:
    void load(const QString& _mod_name);
};

template <class _Mod>
struct mod_qt_translation : basic_qt_translation
{
    void load_translator() { load(_Mod::id); }
};

template <class _Mod>
struct mod_qt : mod<_Mod>, mod_qt_translation<_Mod>
{
    template <class _Type>
    struct qml_type_register
    {
        qml_type_register()
        {
            qmlRegisterType<_Type>(_Mod::qml_pkg_name, _Mod::qml_pkg_ver_major, _Mod::qml_pkg_ver_minor, _Type::qml_name);
        }
    };
    template <class _Type>
    struct qml_alias_register
    {
        void register_as(const char* _qml_name)
        {
            qmlRegisterType<_Type>(_Mod::qml_pkg_name, _Mod::qml_pkg_ver_major, _Mod::qml_pkg_ver_minor, _qml_name);
        }
    };
    template <class _MainObjectTraits, class..._CtorArgs>
    class q_object_init : public main_object_instance<_MainObjectTraits>
    {
    public:
        q_object_init(QObject* _parent, _CtorArgs... _ctorArgs)
            : main_object_instance<_MainObjectTraits>(g_main_repo.load<_MainObjectTraits,QObject*,_CtorArgs...>(_parent, _ctorArgs...))
        {
        }
        ~q_object_init()
        {
            g_main_repo.unload(_MainObjectTraits::id);
        }
    };
    template <class _MainObjectTraits, class..._CtorArgs>
    class qml_singleton_init : public q_object_init<_MainObjectTraits, _CtorArgs...>
    {
    public:
        qml_singleton_init(_CtorArgs... _ctorArgs)
            : q_object_init<_MainObjectTraits, _CtorArgs...>(Q_NULLPTR, _ctorArgs...)
        {
            qmlRegisterSingletonType<typename _MainObjectTraits::Class>(_Mod::qml_pkg_name, _Mod::qml_pkg_ver_major, _Mod::qml_pkg_ver_minor,
                    _MainObjectTraits::qml_name, singleton_provider);
        }
        static QObject* singleton_provider(QQmlEngine*, QJSEngine*)
        {
            main_object<_MainObjectTraits> singleton_object;
            return singleton_object.get();
        }
    };
};

arh_ns_end


#endif // __SYMBOID_SDK_APP_MODQT_H__
