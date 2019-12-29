
#include "sdk/basics/stringutils.h"
#include "sdk/basics/typecontexts/std_string.h"
#include <sstream>

namespace Sy {

template<>
string_a<ctx::types::std_string>::string_a(const Char* buffer, Size length)
    : std::string(buffer ? buffer : "", buffer ? length : 0)
{
}

template<>
std::string string_a<ctx::types::std_string>::std() const
{
    return *this;
}

template<>
string_a<ctx::types::std_string> string_a<ctx::types::std_string>::left(Size length) const
{
    return std::string::substr(0, length);
}

template<>
string_a<ctx::types::std_string> string_a<ctx::types::std_string>::mid(Pos pos, Size length) const
{
    return std::string::substr(pos, length);
}

template<>
string_a<ctx::types::std_string> string_a<ctx::types::std_string>::mid(Pos pos) const
{
    return std::string::substr(pos);
}

template<>
string_a<ctx::types::std_string> string_a<ctx::types::std_string>::right(Size length) const
{
    return std::string::substr(std::string::size() - length);
}

template <typename char_t>
std::list<std::basic_string<char_t>> split(const std::basic_string<char_t>& str, const char_t& delimiter)
{
    std::list<std::basic_string<char_t>> tokenList;
    if (!str.empty())
    {
        std::basic_stringstream<char_t> strStream(str);
        std::basic_string<char_t> token;
        while (std::getline(strStream, token, delimiter))
        {
            tokenList.push_back(token);
        }
    }
    return tokenList;
}

template<>
std::list<std::string> string_list_a<ctx::types::std_string>::splitString(const std::string& str,
        const char& delimiter)
{
    return split(str, delimiter);
}

template<>
std::string string_a<ctx::types::std_wstring>::std() const
{
    return std::string(this->begin(), this->end());
}

template<>
std::list<std::wstring> string_list_a<ctx::types::std_wstring>::splitString(const std::wstring& str,
        const wchar_t& delimiter)
{
    return split(str, delimiter);
}

} // namespace sy
