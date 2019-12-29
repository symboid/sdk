
#include "sdk/basics/json.h"

namespace Sy {

template <>
json_object_a<ctx::types::q_json_object>::json_object_a()
{
}

template <>
int json_object_a<ctx::types::q_json_object>::childCount() const
{
    return mBackend.count();
}

template <>
typename json_object_a<ctx::types::q_json_object>::ValueRef
json_object_a<ctx::types::q_json_object>::operator[](const Key& key)
{
    return mBackend[key];
}

} // namespace Sy
