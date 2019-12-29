
#ifndef __SYMBOID_SDK_BASICS_STRINGUTILS_H__
#define __SYMBOID_SDK_BASICS_STRINGUTILS_H__

#include "ctx/config.h"

namespace Sy {

template <class _ctx_string>
struct string_a : public _ctx_string::self_t
{
    typedef typename _ctx_string::self_t Base;
    typedef typename _ctx_string::char_t Char;
    typedef typename _ctx_string::size_t Size;
    typedef Size Pos;

    string_a() : Base() {}
    string_a(const Base& src) : Base(src) {}
    string_a(const Char* buffer) : Base(buffer ? buffer : "") {}
    string_a(const Char* buffer, Size length);
    template <class _local_ctx_string>
    string_a(const string_a<_local_ctx_string>& src) : Base(src.std().c_str()) {}

    std::string std() const;

    template <class _local_ctx_string>
    string_a<_local_ctx_string> toString() const { return string_a<_local_ctx_string>(*this); }

    string_a<_ctx_string> left(Size length) const;
    string_a<_ctx_string> mid(Pos pos, Size length) const;
    string_a<_ctx_string> mid(Pos pos) const;
    string_a<_ctx_string> right(Size length) const;
};

typedef string_a<ctx::string> String;

template <>
std::string string_a<ctx::types::std_string>::std() const;

template <>
std::string string_a<ctx::types::std_wstring>::std() const;


template <class _ctx_string>
struct string_list_a : public _ctx_string::list_t
{
    typedef typename _ctx_string::self_t Base;
    typedef typename _ctx_string::char_t Char;
    typedef typename _ctx_string::list_t List;

    string_list_a()
    {
    }
    string_list_a(const List& src)
        : List(src)
    {
    }
    template <class _local_ctx_string>
    string_list_a(const string_list_a<_local_ctx_string>& src)
    {
        for (string_a<_local_ctx_string> srcItem : src)
        {
            this->push_back(string_a<_ctx_string>(srcItem));
        }

    }
    static List splitString(const Base& str, const Char& delimiter);

    string_list_a& operator << (const string_a<_ctx_string>& element)
    {
        this->push_back(element);
        return *this;
    }

    template <class _local_ctx_string = _ctx_string>
    string_a<_local_ctx_string> toString(const typename _local_ctx_string::char_t& separator) const
    {
        string_a<_local_ctx_string> string;
        typename string_list_a<_local_ctx_string>::const_iterator item = this->begin(), end = this->end();
        if (item != end)
        {
            string = *item;
            while (++item != end)
            {
                string += separator;
                string += *item;
            }
        }
        return string;
    }
};

typedef string_list_a<ctx::string> StringList;

template<>
std::list<std::string> string_list_a<ctx::types::std_string>::splitString(const std::string& str,
        const char& delimiter);

template<>
std::list<std::wstring> string_list_a<ctx::types::std_wstring>::splitString(const std::wstring& str,
        const wchar_t& delimiter);

} // namespace sy

#endif // __SYMBOID_SDK_BASICS_STRINGUTILS_H__
