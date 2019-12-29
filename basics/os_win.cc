
#include "sdk/basics/os.h"
#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <cstdlib>
#include <cstring>

namespace Sy {

static bool osProcessStart(const String& command, const os_a<ctx::os::win>::ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch)
{
    String parameters = command + " " + arguments.toString(' ');
    String cwd = workingDirPath.toString();

    ULONG execMask(SEE_MASK_NOCLOSEPROCESS);
    if (processLaunch & PROCESS_WAIT)
    {
        execMask = execMask | SEE_MASK_NOASYNC;
    }

    SHELLEXECUTEINFOA shExInfo;
    ZeroMemory(&shExInfo, sizeof(shExInfo));
    shExInfo.cbSize = sizeof(shExInfo);
    shExInfo.fMask = execMask;
    shExInfo.hwnd = nullptr;
    shExInfo.lpVerb = (processLaunch & PROCESS_ELEVATED) ? "runas" : "open";
    shExInfo.lpFile = command.c_str();
    shExInfo.lpParameters = parameters.c_str();
    shExInfo.lpDirectory = cwd.c_str();
    shExInfo.nShow = SW_SHOW;
    shExInfo.hInstApp = nullptr;

    return ShellExecuteExA(&shExInfo) == TRUE;
}

bool os_a<ctx::os::win>::processStart(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch)
{
    return osProcessStart(command, arguments, currentDir(), processLaunch);
}

bool os_a<ctx::os::win>::processStart(const String& command, const ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch)
{
    return osProcessStart(command, arguments, workingDirPath, processLaunch);
}

bool os_a<ctx::os::win>::processExec(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch)

{
    return osProcessStart(command, arguments, currentDir(), processLaunch | PROCESS_WAIT);
}

os_a<ctx::os::win>::FilePath os_a<ctx::os::win>::currentDir()
{
    String::Char buffer[MAX_PATH];
    if (GetCurrentDirectoryA(MAX_PATH, buffer) == std::strlen(buffer))
    {
        return FilePath(buffer);
    }
    else
    {
        return "";
    }
}

bool os_a<ctx::os::win>::exists(const FilePath& filePath)
{
    String filePathStr(filePath.toString());
    return PathFileExistsA(filePathStr.c_str()) == TRUE;
}

os_a<ctx::os::win>::String os_a<ctx::os::win>::getenv(const String& envVarName)
{
    return std::getenv(envVarName.c_str());
}

void os_a<ctx::os::win>::setenv(const String& envVarName, const String& envVarValue)
{
    _putenv_s(envVarName.c_str(), envVarValue.c_str());
}

} // namespace Sy
