
#include "sdk/basics/os.h"
#import <Foundation/Foundation.h>
#include <cstdlib>

namespace Sy {

static bool osProcessStart(const String& command, const os_a<ctx::os::mac>::ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch)
{
    String commandLine = command + " " + arguments.toString(' ');

    // setting up current dir:
    String cwdStr = workingDirPath.toString();
    NSString* cwd = [NSString stringWithUTF8String:cwdStr.c_str()];
    NSLog(@"CWD = %@", cwd);

    // formulating shell script:
    NSString* cmd = [NSString stringWithUTF8String:commandLine.c_str()];
    NSString* ldLibraryPath = [NSString stringWithUTF8String:os_a<ctx::os::mac>::getenv("DYLD_LIBRARY_PATH").c_str()];
    NSString* shellScript = nil;
    if (processLaunch & PROCESS_WAIT)
    {
        shellScript = [NSString stringWithFormat:@"cd %@;export DYLD_LIBRARY_PATH=%@;%@ >/dev/null 2>&1", cwd, ldLibraryPath, cmd];
    }
    else
    {
        shellScript = [NSString stringWithFormat:@"cd %@;export DYLD_LIBRARY_PATH=%@;%@ >/dev/null 2>&1 &", cwd, ldLibraryPath, cmd];
    }
    // formulating Apple script:
    NSString* privileges = [NSString stringWithFormat:@"%@ administrator privileges",
            ((processLaunch & PROCESS_ELEVATED)?@"with":@"without")];
    NSString* scriptSource = [NSString stringWithFormat:@"do shell script \"%@\" %@", shellScript, privileges];
    NSAppleScript* appleScript = [[NSAppleScript new] initWithSource:scriptSource];

    // executing Apple script:
    NSDictionary* errorInfo = [NSDictionary new];
    if ([appleScript executeAndReturnError:&errorInfo])
    {
        NSLog(@"Command '%@' has been successfully executed.", cmd);
        return YES;
    }
    else
    {
        NSLog(@"Failed to execute command '%@'.", cmd);
        return NO;
    }
}

bool os_a<ctx::os::mac>::processStart(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch)
{
    return osProcessStart(command, arguments, currentDir(), processLaunch);
}

bool os_a<ctx::os::mac>::processStart(const String& command, const ProcessArgs& arguments,
        const FilePath& workingDirPath, ProcessLaunch processLaunch)
{
    return osProcessStart(command, arguments, workingDirPath, processLaunch);
}

bool os_a<ctx::os::mac>::processExec(const String& command, const ProcessArgs& arguments,
        ProcessLaunch processLaunch)

{
    return osProcessStart(command, arguments, currentDir(), processLaunch | PROCESS_WAIT);
}

FilePath os_a<ctx::os::mac>::currentDir()
{
    NSString* currentDirStr = [[NSFileManager defaultManager] currentDirectoryPath];
    return FilePath([currentDirStr UTF8String]);
}

bool os_a<ctx::os::mac>::exists(const FilePath& filePath)
{
    String filePathString = filePath.toString();
    NSString* filePathNS =[NSString stringWithUTF8String:filePathString.c_str()];
    return [[NSFileManager defaultManager] fileExistsAtPath:filePathNS] == YES;
}

String os_a<ctx::os::mac>::getenv(const String& envVarName)
{
    return std::getenv(envVarName.c_str());
}

void os_a<ctx::os::mac>::setenv(const String& envVarName, const String& envVarValue)
{
    ::setenv(envVarName.c_str(), envVarValue.c_str(), 1);
}

os_a<ctx::os::mac>::String os_a<ctx::os::mac>::diskSerial()
{
    String diskSerialStr;
    NSTask* shellTask = [[NSTask alloc] init];
    [shellTask setLaunchPath:@"/bin/bash"];
    [shellTask setArguments:@[@"-c", @"system_profiler SPSerialATADataType SPParalelATADataType -detailLevel medium | grep Serial | sed \"s/^.*: //\" | sed \"s/[\\ \\\"\\<\\>]//g\""]];

    NSPipe* pipe = [NSPipe pipe];
    [shellTask setStandardOutput:pipe];

    [shellTask launch];
    NSData* output = [[pipe fileHandleForReading] readDataToEndOfFile];
    [shellTask waitUntilExit];

    NSString* serialStr = [[NSString alloc] initWithData:output encoding:NSUTF8StringEncoding];
    if (serialStr != nil)
    {
        NSUInteger serialLength = [serialStr length];
        // cutting the trailing \n character if exists:
        if ([serialStr characterAtIndex:(serialLength - 1)] == '\n')
        {
            serialStr = [serialStr substringToIndex:(serialLength - 1)];
        }
        diskSerialStr = [serialStr UTF8String];
    }
    return diskSerialStr;
}

} // namespace Sy
