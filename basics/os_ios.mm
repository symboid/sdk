
#include "sdk/basics/os.h"
#import <Foundation/Foundation.h>
#include <cstdlib>

namespace Sy {

FilePath os_a<ctx::os::ios>::currentDir()
{
    NSString* currentDirStr = [[NSFileManager defaultManager] currentDirectoryPath];
    return FilePath([currentDirStr UTF8String]);
}

bool os_a<ctx::os::ios>::exists(const FilePath& filePath)
{
    String filePathString = filePath.toString();
    NSString* filePathNS =[NSString stringWithUTF8String:filePathString.c_str()];
    return [[NSFileManager defaultManager] fileExistsAtPath:filePathNS] == YES;
}

String os_a<ctx::os::ios>::getenv(const String& envVarName)
{
    return std::getenv(envVarName.c_str());
}

void os_a<ctx::os::ios>::setenv(const String& envVarName, const String& envVarValue)
{
    ::setenv(envVarName.c_str(), envVarValue.c_str(), 1);
}

} // namespace Sy
