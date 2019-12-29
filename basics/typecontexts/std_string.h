
#ifndef __SYMBOID_SDK_BASICS_TYPECONTEXTS_STD_STRING_H__
#define __SYMBOID_SDK_BASICS_TYPECONTEXTS_STD_STRING_H__

#include <string>
#include <list>

namespace ctx {

namespace types {

struct std_string
{
    typedef std::string self_t;
    typedef char char_t;
    typedef std::list<std::string> list_t;
    typedef std::string::size_type size_t;
};

struct std_wstring
{
    typedef std::wstring self_t;
    typedef wchar_t char_t;
    typedef std::list<std::wstring> list_t;
    typedef std::wstring::size_type size_t;
};

} // namespace types

} // namespace ctx

#endif // __SYMBOID_SDK_BASICS_TYPECONTEXTS_STD_STRING_H__
