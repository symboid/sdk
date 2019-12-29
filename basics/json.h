
#ifndef __SYMBOID_SDK_BASICS_JSON_H__
#define __SYMBOID_SDK_BASICS_JSON_H__

#include "ctx/config.h"
#include "sdk/basics/typecontexts/q_json_object.h"
#include "sdk/basics/stringutils.h"

namespace ctx {

// default json type
typedef types::q_json_object json_object;

} // namespace ctx

namespace Sy {

template <class _ctx_json_object>
struct json_object_a
{
    typedef typename _ctx_json_object::key_t Key;
    typedef typename _ctx_json_object::value_ref_t ValueRef;
    typedef typename _ctx_json_object::const_value_ref_t ConstValueRef;
    typedef typename _ctx_json_object::iterator_t Iterator;
    typedef typename _ctx_json_object::const_iterator_t ConstIterator;

    json_object_a();

    int childCount() const;
    ConstValueRef operator[](const Key& key) const;
    ValueRef operator[](const Key& key);

private:
    typename _ctx_json_object::backend_t mBackend;
};

typedef json_object_a<ctx::json_object> JsonObject;

template <> json_object_a<ctx::json_object>::json_object_a();
template <> int json_object_a<ctx::json_object>::childCount() const;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_JSON_H__
