
#ifndef __SYMBOID_SDK_BASICS_CONTEXTS_H__
#define __SYMBOID_SDK_BASICS_CONTEXTS_H__

namespace ctx {

// os context
namespace os {

struct win
{
    static constexpr char dirsep = '\\';
};

struct posix
{
    static constexpr char dirsep = '/';
};

struct mac : posix {};

struct ios : posix {};

struct lin : posix {};

struct adr : posix {};

} // namespace os

// build config contexts
namespace build {

struct debug
{
    static constexpr const char* name = "debug";
};

struct release
{
    static constexpr const char* name = "release";
};

} // namespace build

// running contexts
namespace run {

struct prod {};

struct dev {};

struct qmake {};

} // namespace run

} // namespace ctx

#endif // __SYMBOID_SDK_BASICS_CONTEXTS_H__
