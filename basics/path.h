
#ifndef __SYMBOID_SDK_BASICS_PATH_H__
#define __SYMBOID_SDK_BASICS_PATH_H__

#include "ctx/config.h"
#include "sdk/basics/stringutils.h"

namespace Sy {

template <class _ctx_string, typename _ctx_string::char_t SEPARATOR>
struct path_a : string_list_a<_ctx_string>
{
    typedef string_a<_ctx_string> String;
    typedef typename String::Char Char;
    typedef string_list_a<_ctx_string> List;

    path_a()
    {
    }
    path_a(const String& pathStr)
        : List(List::splitString(pathStr, SEPARATOR))
    {
    }
    path_a(const typename String::Base& pathStr)
        : List(List::splitString(String(pathStr), SEPARATOR))
    {
    }
    path_a(const Char* pathCStr)
        : List(List::splitString(pathCStr, SEPARATOR))
    {
    }
    template <class _local_ctx_string, typename _local_ctx_string::char_t OTHER_SEPARATOR>
    path_a(const path_a<_local_ctx_string,OTHER_SEPARATOR>& src)
        : List(src)
    {
    }

    path_a operator / (const path_a& relPath) const
    {
        path_a newPath(*this);
        for (String fileName : relPath)
        {
            newPath.push_back(fileName);
        }
        return newPath;
    }

    String toString() const
    {
        return List::toString(SEPARATOR);
    }
    operator String() const
    {
        return toString();
    }

    path_a parent() const
    {
        path_a dirPath(*this);
        dirPath.pop_back();
        return dirPath;
    }
    String baseName() const
    {
        return this->back();
    }
};

typedef path_a<ctx::string, ctx::os::current::dirsep> FilePath;

} // namespace sy

#endif // __SYMBOID_SDK_BASICS_PATH_H__
