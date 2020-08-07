
#ifndef __SYMBOID_SDK_ARCH_MAINOBJECT_H__
#define __SYMBOID_SDK_ARCH_MAINOBJECT_H__

#include "sdk/arch/defs.h"
#include "sdk/arch/mainrepo.h"
#include <mutex>
#include "sdk/arch/log.h"

arh_ns_begin

template <class _MainObjectTraits>
class main_object_instance
{
public:
    typedef typename _MainObjectTraits::Class Class;

public:
    main_object_instance(main_repo::item<_MainObjectTraits>* _repo_item)
        : _M_repo_item(_repo_item)
    {
    }

protected:
    main_repo::item<_MainObjectTraits>* _M_repo_item;

public:
    Class* operator->() { return _M_repo_item->_M_object; }
    const Class* operator->() const { return _M_repo_item->_M_object; }

    Class* get() { return _M_repo_item->_M_object; }
    const Class* get() const { return _M_repo_item->_M_object; }

    bool is_null() const { return !_M_repo_item || !_M_repo_item->_M_object; }
    operator bool () const { return _M_repo_item && _M_repo_item->_M_object; }
};

template <class _MainObjectTraits>
class main_object_sync : public main_object_instance<_MainObjectTraits>
{
    using main_object_instance<_MainObjectTraits>::_M_repo_item;

public:
    main_object_sync(main_repo::item<_MainObjectTraits>* _repo_item)
        : main_object_instance<_MainObjectTraits>(_repo_item)
        , _M_access_guard(_repo_item->mutex())
    {
        _M_repo_item->add_ref();
    }
    main_object_sync() :
        main_object_sync(g_main_repo.find<_MainObjectTraits>())
    {
    }
    ~main_object_sync()
    {
        _M_repo_item->release();
    }

private:
    main_object_guard _M_access_guard;
};

template <class _MainObjectTraits>
class main_object : public main_object_instance<_MainObjectTraits>
{
    using main_object_instance<_MainObjectTraits>::_M_repo_item;

public:
    main_object() :
        main_object_instance<_MainObjectTraits>(g_main_repo.find<_MainObjectTraits>())
    {
        if (_M_repo_item)
        {
            _M_repo_item->add_ref();
        }
        else
        {
            log_error << "main object '" << _MainObjectTraits::id << "' not found!";
        }
    }
    ~main_object()
    {
        if (_M_repo_item)
        {
            _M_repo_item->release();
        }
    }

public:
    main_object_sync<_MainObjectTraits> sync() { return main_object_sync<_MainObjectTraits>(_M_repo_item); }
    const main_object_sync<_MainObjectTraits> sync() const { return main_object_sync<_MainObjectTraits>(_M_repo_item); }
};

template <class _MainObjectTraits, class..._CtorArgs>
class main_object_init : public main_object_instance<_MainObjectTraits>
{
public:
    main_object_init(_CtorArgs... _ctorArgs)
        : main_object_instance<_MainObjectTraits>(g_main_repo.load<_MainObjectTraits,_CtorArgs...>(_ctorArgs...))
    {
    }
    ~main_object_init()
    {
        g_main_repo.unload(_MainObjectTraits::id);
    }
};

arh_ns_end

#define __MAIN_OBJECT(_MainObjectClass,_main_object_name,_main_object_type, _owner_is_repo) \
public: \
    typedef _MainObjectClass Class; \
    static constexpr const char* id = #_main_object_name; \
    static constexpr const char* type_str = #_main_object_type; \
    static constexpr bool owner_is_repo = _owner_is_repo; \
    typedef arh::main_object<_MainObjectClass> mo;

#define MAIN_OBJECT(_MainObjectClass, _main_object_name) \
    __MAIN_OBJECT(_MainObjectClass, _main_object_name, main object, true)

#define Q_MAIN_OBJECT(_main_object_name, _main_object_type) \
    __MAIN_OBJECT(Q##_main_object_name, _main_object_name, _main_object_type, false)

#define QML_SINGLETON(_qml_name) \
    Q_MAIN_OBJECT(_qml_name, qml singleton) \
public: \
    static constexpr const char* qml_name = id;

#endif // __SYMBOID_SDK_ARCH_MAINOBJECT_H__
