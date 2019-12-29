
#include "sdk/basics/stringutils.h"
#include "sdk/basics/typecontexts/q_string.h"

namespace Sy {

template<>
string_a<ctx::types::q_string>::string_a(const Char* buffer, Size length)
    : QString(QString(buffer).left(length))
{
}

template<>
std::string string_a<ctx::types::q_string>::std() const
{
    return this->toStdString();
}

template<>
QStringList string_list_a<ctx::types::q_string>::splitString(const QString& str,
        const char& delimiter)
{
    return str.split(delimiter);
}

template<>
string_a<ctx::types::q_string> string_a<ctx::types::q_string>::left(Size length) const
{
    return QString::left(length);
}

template<>
string_a<ctx::types::q_string> string_a<ctx::types::q_string>::mid(Pos pos, Size length) const
{
    return QString::mid(pos, length);
}

template<>
string_a<ctx::types::q_string> string_a<ctx::types::q_string>::mid(Pos pos) const
{
    return QString::mid(pos);
}

template<>
string_a<ctx::types::q_string> string_a<ctx::types::q_string>::right(Size length) const
{
    return QString::right(length);
}

} // namespace sy
