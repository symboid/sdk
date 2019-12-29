
#ifndef __SYMBOID_SDK_BASICS_SYSTEM_COMPONENT_H__
#define __SYMBOID_SDK_BASICS_SYSTEM_COMPONENT_H__

#include "ctx/config.h"
#include "sdk/basics/stringutils.h"
#include "sdk/basics/path.h"
#include "sdk/basics/system/module.h"

namespace Sy {

template <template<class,class> class _ComponentTraits, class _ctx_run = ctx::run::env>
struct component_a
{
    typedef _ComponentTraits<ctx::os::current,_ctx_run> Traits;

    component_a()
        : mName(Traits::name)
        , mHome(Traits::home())
    {
        if (Traits::homeVar)
        {
            Os::setenv(Traits::homeVar, mHome.toString());
        }
    }

    component_a(const String& name, const FilePath& home)
        : mName(name)
        , mHome(home)
    {
    }

    const String mName;
    const FilePath mHome;

    exe_module_a<_ctx_run> exeModule(const String& moduleId)
    {
        return exe_module_a<_ctx_run>(moduleId, mHome);
    }

    exe_module_a<_ctx_run> exeModule(const String& moduleId, const FilePath& relFolder)
    {
        return exe_module_a<_ctx_run>(moduleId, mHome, relFolder);
    }

    shd_module_a<_ctx_run> shdModule(const String& moduleId)
    {
        return shd_module_a<_ctx_run>(moduleId, mHome);
    }

    shd_module_a<_ctx_run> shdModule(const String& moduleId, const FilePath& relFolder)
    {
        return shd_module_a<_ctx_run>(moduleId, mHome, relFolder);
    }
};

template <class _ctx_os, class _ctx_run>
struct ComponentNullTraits
{
    static constexpr const char* name = nullptr;
    static FilePath home() { return os_a<_ctx_os>::currentDir(); }
    static constexpr const char* homeVar = nullptr;
};

typedef component_a<ComponentNullTraits,ctx::run::env> Component;
typedef component_a<ComponentNullTraits,ctx::run::dev> ComponentDev;
typedef component_a<ComponentNullTraits,ctx::run::qmake> ComponentQmake;
typedef component_a<ComponentNullTraits,ctx::run::prod> ComponentProd;

template <class _ctx_os, class _ctx_run>
struct PlatformTraits;

template <>
struct PlatformTraits<ctx::os::mac,ctx::run::prod>
{
    static constexpr const char* name = "platform";
    static FilePath home() { return "/Library/Symboid/Platform.app"; }
    static constexpr const char* homeVar = "SYMBOID_HOME";
};

template <>
struct PlatformTraits<ctx::os::win,ctx::run::prod>
{
    static constexpr const char* name = "platform";
    static FilePath home() { return FilePath(Os::getenv("ProgramFiles")) / "Symboid" / "Platform"; }
    static constexpr const char* homeVar = "SYMBOID_HOME";
};

template <class _ctx_os>
struct PlatformTraits<_ctx_os,ctx::run::dev>
{
    static constexpr const char* name = "platform";
    static FilePath home() { return os_a<_ctx_os>::currentDir(); }
    static constexpr const char* homeVar = "SYMBOID_HOME_DEV";
};

template <class _ctx_os>
struct PlatformTraits<_ctx_os,ctx::run::qmake>
{
    static constexpr const char* name = "platform";
    static FilePath home() { return os_a<_ctx_os>::currentDir() / name; }
    static constexpr const char* homeVar = "SYMBOID_HOME_DEV";
};

typedef component_a<PlatformTraits,ctx::run::env> PlatformComponent;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_SYSTEM_COMPONENT_H__
