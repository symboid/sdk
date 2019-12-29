
#include "sdk/basics/os.h"
#include <cstdlib>

namespace Sy {

os_a<ctx::os::adr>::FilePath os_a<ctx::os::adr>::currentDir()
{
    {
        return "";
    }
}

bool os_a<ctx::os::adr>::exists(const FilePath& filePath)
{
    String filePathStr(filePath.toString());
    return false;
}

os_a<ctx::os::adr>::String os_a<ctx::os::adr>::getenv(const String& envVarName)
{
    return std::getenv(envVarName.c_str());
}

void os_a<ctx::os::adr>::setenv(const String& envVarName, const String& envVarValue)
{
    //putenv(envVarName.c_str(), envVarValue.c_str());
}

} // namespace Sy
