
#ifndef __SYMBOID_SDK_BASICS_SYSTEM_MODULE_H__
#define __SYMBOID_SDK_BASICS_SYSTEM_MODULE_H__

#include "ctx/config.h"
#include "sdk/basics/stringutils.h"
#include "sdk/basics/path.h"
#include "sdk/basics/os.h"

namespace Sy {

template <class _ctx_os, class _ctx_build, class _ctx_run>
struct ModuleTraits;

template<class _ctx_build>
struct ModuleTraits<ctx::os::mac,_ctx_build,ctx::run::qmake>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome / relPath;
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::lin,_ctx_build,ctx::run::qmake>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome / relPath;
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::adr,_ctx_build,ctx::run::qmake>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome / relPath;
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::win,_ctx_build,ctx::run::qmake>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome / relPath / _ctx_build::name;
    }
};

template<class _ctx_os, class _ctx_build>
struct ModuleTraits<_ctx_os,_ctx_build,ctx::run::dev>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome;
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::win,_ctx_build,ctx::run::prod>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome;
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::mac,_ctx_build,ctx::run::prod>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome / "Contents/MacOS";
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::lin,_ctx_build,ctx::run::prod>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome;
    }
};

template<class _ctx_build>
struct ModuleTraits<ctx::os::adr,_ctx_build,ctx::run::prod>
{
    static FilePath modulePath(const FilePath& componentHome, const FilePath& relPath)
    {
        return componentHome;
    }
};

template <class _ctx_os, class _ctx_build, class _ctx_run>
struct ModuleExeTraits;

template <class _ctx_build, class _ctx_run>
struct ModuleExeTraits<ctx::os::win,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::win,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "";
    static constexpr const char* BASE_NAME_SUFFIX = ".exe";
};

template <class _ctx_build, class _ctx_run>
struct ModuleExeTraits<ctx::os::mac,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::mac,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "";
    static constexpr const char* BASE_NAME_SUFFIX = "";
};

template <class _ctx_build, class _ctx_run>
struct ModuleExeTraits<ctx::os::lin,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::lin,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "";
    static constexpr const char* BASE_NAME_SUFFIX = "";
};

template <class _ctx_build, class _ctx_run>
struct ModuleExeTraits<ctx::os::adr,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::adr,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "";
    static constexpr const char* BASE_NAME_SUFFIX = "";
};

template <class _ctx_os, class _build, class _run>
struct ModuleShdTraits;

template <class _ctx_build, class _ctx_run>
struct ModuleShdTraits<ctx::os::win,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::win,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "";
    static constexpr const char* BASE_NAME_SUFFIX = ".dll";
};

template <class _ctx_build, class _ctx_run>
struct ModuleShdTraits<ctx::os::mac,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::mac,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "lib";
    static constexpr const char* BASE_NAME_SUFFIX = ".dylib";
};

template <class _ctx_build, class _ctx_run>
struct ModuleShdTraits<ctx::os::lin,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::lin,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "lib";
    static constexpr const char* BASE_NAME_SUFFIX = ".so";
};

template <class _ctx_build, class _ctx_run>
struct ModuleShdTraits<ctx::os::adr,_ctx_build,_ctx_run> : ModuleTraits<ctx::os::adr,_ctx_build,_ctx_run>
{
    static constexpr const char* BASE_NAME_PREFIX = "lib";
    static constexpr const char* BASE_NAME_SUFFIX = ".so";
};

template <template <class, class, class> class _ModuleTraits, class _ctx_run = ctx::run::env>
struct module_a : _ModuleTraits<ctx::os::current, ctx::build::config, _ctx_run>
{
    typedef _ModuleTraits<ctx::os::current, ctx::build::config, _ctx_run> Base;

    module_a(const String& name, const FilePath& componentHome)
        : mName(name)
        , mLocation(Base::modulePath(componentHome, name))
        , mBaseName(String(Base::BASE_NAME_PREFIX) + name + Base::BASE_NAME_SUFFIX)
        , mBinaryPath(mLocation / mBaseName)
        , mExists(Os::exists(mBinaryPath))
    {
    }

    module_a(const String& name, const FilePath& componentHome, const FilePath& relPath)
        : mName(name)
        , mLocation(Base::modulePath(componentHome, relPath))
        , mBaseName(String(Base::BASE_NAME_PREFIX) + name + Base::BASE_NAME_SUFFIX)
        , mBinaryPath(mLocation / mBaseName)
        , mExists(Os::exists(mBinaryPath))
    {
    }

    const String mName;
    const FilePath mLocation;
    const String mBaseName;
    const FilePath mBinaryPath;
    const bool mExists;
};

template <class _ctx_run >
struct exe_module_a : public module_a<ModuleExeTraits,_ctx_run>
{
#ifdef _MSC_VER
    typedef module_a module_b;
#else
    typedef module_a<ModuleExeTraits,_ctx_run> module_b;
#endif

    exe_module_a<_ctx_run>(const String& name, const FilePath& componentHome)
        : module_b(name, componentHome)
    {
    }

    exe_module_a<_ctx_run>(const String& name, const FilePath& componentHome, const FilePath& relPath)
        : module_b(name, componentHome, relPath)
    {
    }

    Os::ProcessArgs mArguments;
    exe_module_a& addArgument(const String& argOption)
    {
        mArguments << argOption;
        return *this;
    }
    exe_module_a& addParameter(const String& argName, const String& argValue)
    {
        return addArgument(String("--") + argName + ":" + argValue);
    }

    bool launch(ProcessLaunch processLaunch = PROCESS_NORMAL)
    {
        Os::FilePath exePath(this->mBinaryPath);
        return this->mExists && Os::processStart(exePath, mArguments, processLaunch);
    }
    bool launch(const FilePath& workingDir, ProcessLaunch processLaunch = PROCESS_NORMAL)
    {
        const Os::FilePath exePath(this->mBinaryPath);
        return this->mExists && Os::processStart(exePath, mArguments, workingDir, processLaunch);
    }
    bool launchElevated()
    {
        return launch(PROCESS_ELEVATED);
    }
};

typedef exe_module_a<ctx::run::env> ExeModule;

template <class _ctx_run>
struct shd_module_a : public module_a<ModuleShdTraits,_ctx_run>
{
#ifdef _MSC_VER
    typedef module_a module_b;
#else
    typedef module_a<ModuleShdTraits,_ctx_run> module_b;
#endif

    shd_module_a(const String& name, const FilePath& location)
        : module_b(name, location)
    {
    }
    shd_module_a(const String& name, const FilePath& location, const FilePath& relPath)
        : module_b(name, location, relPath)
    {
    }
};

typedef shd_module_a<ctx::run::env> ShdModule;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_SYSTEM_MODULE_H__
