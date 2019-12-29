
#ifndef __SYMBOID_SDK_BASICS_OS_H__
#define __SYMBOID_SDK_BASICS_OS_H__

#include "ctx/config.h"
#include "sdk/basics/stringutils.h"
#include "sdk/basics/path.h"

namespace Sy {

typedef int ProcessLaunch;

constexpr const ProcessLaunch PROCESS_NORMAL       = 0x00;
constexpr const ProcessLaunch PROCESS_ELEVATED     = 0x01;
constexpr const ProcessLaunch PROCESS_WAIT         = 0x02;

template <class _ctx_os>
struct os_a;

template <>
struct os_a<ctx::os::win>
{
    typedef string_a<ctx::types::std_string> String;
    typedef path_a<ctx::types::std_string, ctx::os::win::dirsep> FilePath;
    typedef string_list_a<ctx::types::std_string> ProcessArgs;


    static bool processStart(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch = PROCESS_NORMAL);
    static bool processStart(const String& command, const ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch = PROCESS_NORMAL);
    static bool processExec(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch = PROCESS_NORMAL);

    static FilePath currentDir();

    static bool exists(const FilePath& filePath);

    static String getenv(const String& envVarName);
    static void setenv(const String& envVarName, const String& envVarValue);
};

template <>
struct os_a<ctx::os::mac>
{
    typedef string_a<ctx::types::std_string> String;
    typedef path_a<ctx::types::std_string, ctx::os::mac::dirsep> FilePath;
    typedef string_list_a<ctx::types::std_string> ProcessArgs;

    static bool processStart(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch = PROCESS_NORMAL);
    static bool processStart(const String& command, const ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch = PROCESS_NORMAL);
    static bool processExec(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch = PROCESS_NORMAL);

    static FilePath currentDir();

    static bool exists(const FilePath& filePath);

    static String getenv(const String& envVarName);
    static void setenv(const String& envVarName, const String& envVarValue);

    static String diskSerial();
};

template <>
struct os_a<ctx::os::ios>
{
    typedef string_a<ctx::types::std_string> String;
    typedef path_a<ctx::types::std_string, ctx::os::ios::dirsep> FilePath;

    static FilePath currentDir();

    static bool exists(const FilePath& filePath);

    static String getenv(const String& envVarName);
    static void setenv(const String& envVarName, const String& envVarValue);

    /// TODO: remove after liccrypt(elemetum) eliminated
    static String diskSerial();
};

template <>
struct os_a<ctx::os::lin>
{
    typedef string_a<ctx::types::std_string> String;
    typedef path_a<ctx::types::std_string, ctx::os::lin::dirsep> FilePath;
    typedef string_list_a<ctx::types::std_string> ProcessArgs;

    static bool processStart(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch = PROCESS_NORMAL);
    static bool processStart(const String& command, const ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch = PROCESS_NORMAL);
    static bool processExec(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch = PROCESS_NORMAL);

    static FilePath currentDir();

    static bool exists(const FilePath& filePath);

    static String getenv(const String& envVarName);
    static void setenv(const String& envVarName, const String& envVarValue);

    static String diskSerial();
};

template <>
struct os_a<ctx::os::adr>
{
    typedef string_a<ctx::types::std_string> String;
    typedef path_a<ctx::types::std_string, ctx::os::adr::dirsep> FilePath;

    static FilePath currentDir();

    static bool exists(const FilePath& filePath);

    static String getenv(const String& envVarName);
    static void setenv(const String& envVarName, const String& envVarValue);

    /// TODO: remove after liccrypt(elemetum) eliminated
    static String diskSerial();
};

typedef os_a<ctx::os::current> Os;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_OS_H__
