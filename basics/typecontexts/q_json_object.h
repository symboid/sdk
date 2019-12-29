
#ifndef __SYMBOID_SDK_BASICS_TYPECONTEXTS_Q_JSON_OBJECT_H__
#define __SYMBOID_SDK_BASICS_TYPECONTEXTS_Q_JSON_OBJECT_H__

#include <QString>
#include <QJsonObject>

namespace ctx {

namespace types {

struct q_json_object
{
    typedef QString key_t;
    typedef QJsonObject backend_t;
    typedef QJsonValueRef value_ref_t;
    typedef const QJsonValueRef const_value_ref_t;
    typedef QJsonObject::iterator iterator_t;
    typedef QJsonObject::const_iterator const_iterator_t;
};

} // namespace types

} // namespace ctx

#endif // __SYMBOID_SDK_BASICS_TYPECONTEXTS_Q_JSON_OBJECT_H__
