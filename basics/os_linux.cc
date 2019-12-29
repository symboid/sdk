
#include "sdk/basics/os.h"
#include <cstdlib>

namespace Sy {

static bool osProcessStart(const String& command, const os_a<ctx::os::lin>::ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch)
{
    return false;
}

bool os_a<ctx::os::lin>::processStart(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch)
{
    return osProcessStart(command, arguments, currentDir(), processLaunch);
}

bool os_a<ctx::os::lin>::processStart(const String& command, const ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch)
{
    return osProcessStart(command, arguments, workingDirPath, processLaunch);
}

bool os_a<ctx::os::lin>::processExec(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch)

{
    return osProcessStart(command, arguments, currentDir(), processLaunch | PROCESS_WAIT);
}

os_a<ctx::os::lin>::FilePath os_a<ctx::os::lin>::currentDir()
{
    {
        return "";
    }
}

bool os_a<ctx::os::lin>::exists(const FilePath& filePath)
{
    String filePathStr(filePath.toString());
    return false;
}

os_a<ctx::os::lin>::String os_a<ctx::os::lin>::getenv(const String& envVarName)
{
    return std::getenv(envVarName.c_str());
}

void os_a<ctx::os::lin>::setenv(const String& envVarName, const String& envVarValue)
{
    //putenv(envVarName.c_str(), envVarValue.c_str());
}

} // namespace Sy
