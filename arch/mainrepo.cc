
#include "sdk/arch/setup.h"
#include "sdk/arch/mainrepo.h"
#include "sdk/arch/log.h"

arh_ns_begin

main_repo::basic_item::basic_item(const char* _item_type_str, bool _owned_by_repo)
    : _M_item_type_str(_item_type_str)
    , _M_owned_by_repo(_owned_by_repo)
{
}

void main_repo::basic_item::add_ref()
{
    main_object_guard ref_count_guard(_M_access_mutex);
    _M_ref_count++;
}
void main_repo::basic_item::release()
{
    main_object_guard ref_count_guard(_M_access_mutex);
    _M_ref_count--;
}
int main_repo::basic_item::ref_count() const
{
    return _M_ref_count;
}
main_object_mutex& main_repo::basic_item::mutex()
{
    return _M_access_mutex;
}

void main_repo::add(const std::string& _main_object_id, basic_item* _main_object)
{
    objects_guard objects_guard(_M_objects_access_mutex);
    objects::iterator item_it = _M_objects.find(_main_object_id);
    if (item_it != _M_objects.end())
    {
        item_it->second->add_ref();
    }
    else
    {
        _main_object->add_ref();
        _M_objects[_main_object_id] = _main_object;
        log_info << _main_object->_M_item_type_str << " '" << _main_object_id << "' loaded.";
    }
}

void main_repo::find(const std::string &_main_object_id, basic_item*& _main_object)
{
    objects_guard objects_guard(_M_objects_access_mutex);
    objects::const_iterator item_it = _M_objects.find(_main_object_id);
    _main_object = (item_it != _M_objects.end()) ? item_it->second : nullptr;
}

void main_repo::unload(const std::string& _main_object_id)
{
    objects_guard objects_guard(_M_objects_access_mutex);
    objects::const_iterator object_it = _M_objects.find(_main_object_id);
    if (object_it != _M_objects.end())
    {
        basic_item* to_unload = object_it->second;
        to_unload->release();
        if (to_unload->ref_count() == 0)
        {
            _M_objects.erase(object_it);
            if (to_unload->_M_owned_by_repo)
            {
                std::string item_type_str(to_unload->_M_item_type_str);
                delete to_unload;
                log_info << item_type_str << " '" << _main_object_id << "' unloaded and deleted.";
            }
            else
            {
                log_info << to_unload->_M_item_type_str << " '" << _main_object_id << "' unloaded.";
            }
        }
    }
}

main_repo g_main_repo;

arh_ns_end
