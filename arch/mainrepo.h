
#ifndef __SYMBOID_SDK_ARCH_MAINREPO_H__
#define __SYMBOID_SDK_ARCH_MAINREPO_H__

#include "sdk/arch/defs.h"
#include <string>
#include <mutex>
#include <map>

arh_ns_begin

template <class _Class, class... _CtorArgs>
_Class* main_object_create(_CtorArgs... _ctorArgs)
{
    return new _Class(_ctorArgs...);
}

typedef std::recursive_mutex main_object_mutex;
typedef std::lock_guard<main_object_mutex> main_object_guard;

class SDK_ARCH_API main_repo
{
public:
    class SDK_ARCH_API basic_item
    {
    public:
        basic_item(const char* _item_type_str, bool _owned_by_repo);
        virtual ~basic_item() = default;
    private:
        int _M_ref_count = 0;
        main_object_mutex _M_access_mutex;
    public:
        const char* const _M_item_type_str;
        const bool _M_owned_by_repo;
    public:
        void add_ref();
        void release();
        int ref_count() const;
        main_object_mutex& mutex();
    };

    template <class _MainObjectTraits>
    struct item : basic_item
    {
        template <class... _CtorArgs>
        item(_CtorArgs... _ctorArgs)
            : basic_item(_MainObjectTraits::type_str, _MainObjectTraits::owner_is_repo)
            , _M_object(main_object_create<typename _MainObjectTraits::Class,_CtorArgs...>(_ctorArgs...))
        {
        }
        ~item() { delete _M_object; }
        typename _MainObjectTraits::Class* _M_object;
    };

private:
    typedef std::map<std::string, basic_item*> objects;
    objects _M_objects;
    typedef std::recursive_mutex objects_mutex;
    typedef std::lock_guard<objects_mutex> objects_guard;
    objects_mutex _M_objects_access_mutex;

public:
    void add(const std::string& _main_object_id, basic_item* _main_object);
    template <class _MainObjectTraits, class... _ClassCtorArgs>
    item<_MainObjectTraits>* load(_ClassCtorArgs... _ctorArgs)
    {
        item<_MainObjectTraits>* object_item = find<_MainObjectTraits>();
        if (object_item)
        {
            object_item->add_ref();
        }
        else
        {
            object_item = new item<_MainObjectTraits>(_ctorArgs...);
            add(_MainObjectTraits::id, object_item);
        }
        return object_item;
    }

    void find(const std::string& _main_object_id, basic_item*& _main_object);
    template <class _MainObjectTraits>
    item<_MainObjectTraits>* find()
    {
        basic_item* object_item = nullptr;
        find(_MainObjectTraits::id, object_item);
        return reinterpret_cast<item<_MainObjectTraits>*>(object_item);
    }

    void unload(const std::string& _main_object_id);
};

extern SDK_ARCH_API main_repo g_main_repo;

arh_ns_end

#endif // __SYMBOID_SDK_ARCH_MAINREPO_H__
