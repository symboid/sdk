
#ifndef __SYMBOID_SDK_BASICS_TYPECONTEXTS_Q_STRING_H__
#define __SYMBOID_SDK_BASICS_TYPECONTEXTS_Q_STRING_H__

#include <QString>
#include <QStringList>

namespace ctx {

namespace types {

struct q_string
{
    typedef QString self_t;
    typedef char char_t;
    typedef QStringList list_t;
    typedef QString::size_type size_t;
};

} // namespace types

} // namespace ctx

#endif // __SYMBOID_SDK_BASICS_TYPECONTEXTS_Q_STRING_H__
