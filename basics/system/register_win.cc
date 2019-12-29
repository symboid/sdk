
#include "sdk/basics/system/register.h"
#include <windows.h>
#include <cstring>

namespace Sy {

struct WindowsRegister
{
    WindowsRegister(const RegPath& regPath);
    ~WindowsRegister();

    HKEY mEntryKey;

    static constexpr const int BUFFER_LEN = 256;
    BYTE mValueBuffer[BUFFER_LEN + 1];
    DWORD mValueLen;

    bool hasItem(const LPCSTR& itemName);
    bool queryItem(const LPCSTR& itemName, DWORD valueType);
    bool setItem(const LPCSTR& itemName, DWORD valueType);

    String entryName(DWORD itemIndex);

    static constexpr const char* LOCAL_MACHINE = "LOCAL_MACHINE";
    static constexpr const char* CURRENT_USER = "CURRENT_USER";
    static reg_api_a<ctx::os::win>::String sComponentName;
};

WindowsRegister::WindowsRegister(const RegPath& regPath)
    : mEntryKey(nullptr)
    , mValueLen(0)
{
    const String rootPath = regPath.mRootPath.toString();
    const String entryPath = regPath.mEntryPath.toString();

    if (rootPath == LOCAL_MACHINE)
    {
        // full access to LOCAL_MACHINE if permitted (runas mode):
        if ((RegCreateKeyExA(HKEY_LOCAL_MACHINE, entryPath.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &mEntryKey, nullptr)) == ERROR_SUCCESS)
        {
        }
        // readonly access to LOCAL_MACHINE (created by 32-bit installer on 32 bit system or 64-bit installer on 64 bit system):
        else if ((RegOpenKeyExA(HKEY_LOCAL_MACHINE, entryPath.c_str(), 0, KEY_READ, &mEntryKey)) == ERROR_SUCCESS)
        {
        }
        // readonly access to LOCAL_MACHINE (created by 32-bit installer on 64 bit system under WOW6432Node):
        else if ((RegOpenKeyExA(HKEY_LOCAL_MACHINE, entryPath.c_str(), 0, KEY_READ | KEY_WOW64_32KEY, &mEntryKey)) == ERROR_SUCCESS)
        {
        }
    }
    // full access to CURRENT_USER:
    else if (rootPath == CURRENT_USER && RegCreateKeyA(HKEY_CURRENT_USER, entryPath.c_str(), &mEntryKey) == ERROR_SUCCESS)
    {
    }
    else
    {
        mEntryKey = nullptr;
    }
}

WindowsRegister::~WindowsRegister()
{
    if (mEntryKey)
    {
        RegCloseKey(mEntryKey);
    }
}

bool WindowsRegister::hasItem(const LPCSTR& itemName)
{
    bool foundItem = false;
    if (mEntryKey)
    {
        foundItem = (RegQueryValueExA(mEntryKey, itemName, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS);
    }
    return foundItem;
}

bool WindowsRegister::queryItem(const LPCSTR& itemName, DWORD valueType)
{
    bool queryOk(false);
    if (mEntryKey)
    {
        mValueLen = BUFFER_LEN;
        queryOk = (RegQueryValueExA(mEntryKey, itemName, nullptr, &valueType, mValueBuffer, &mValueLen) == ERROR_SUCCESS);
    }
    return queryOk;
}

bool WindowsRegister::setItem(const LPCSTR& itemName, DWORD valueType)
{
    bool setOk(false);
    if (mEntryKey)
    {
        setOk = (RegSetValueExA(mEntryKey, itemName, 0, valueType, mValueBuffer, mValueLen) == ERROR_SUCCESS);
    }
    return setOk;
}

String WindowsRegister::entryName(DWORD itemIndex)
{
    String itemName;
    if (mEntryKey)
    {
        char nameBuffer[BUFFER_LEN + 1];
        DWORD nameLength(BUFFER_LEN);
        if (RegEnumKeyExA(mEntryKey, itemIndex, nameBuffer, &nameLength, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS)
        {
            itemName = nameBuffer;
        }
    }
    return itemName;
}

reg_api_a<ctx::os::win>::String WindowsRegister::sComponentName;

RegPath reg_api_a<ctx::os::win>::adminRoot()
{
    return RegPath(WindowsRegister::LOCAL_MACHINE, "Software\\Symboid\\Components");
}

RegPath reg_api_a<ctx::os::win>::userRoot()
{
    return RegPath(WindowsRegister::CURRENT_USER, "Software\\Symboid\\Components");
}

RegPath reg_api_a<ctx::os::win>::installStampsRoot()
{
    return RegPath(WindowsRegister::LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\SymboidInstallStamps");
}

bool reg_api_a<ctx::os::win>::hasItem(const RegPath& regPath, const String& itemName)
{
    WindowsRegister windowsRegister(regPath);

    // 1) looking for the item as value item:
    bool foundItem = windowsRegister.hasItem(itemName.c_str());

    // 2) looking for the item as sub domain item (if not found as item):
    WORD itemIndex = 0;
    String entryName;
    while (!foundItem && (entryName = windowsRegister.entryName(itemIndex)) != "")
    {
        foundItem = (entryName == itemName);
        ++itemIndex;
    }
    return foundItem;
}

template <>
RegString reg_api_a<ctx::os::win>::getValue<RegString>(const RegPath& regPath, const String& itemName)
{
    WindowsRegister windowsRegister(regPath);
    return windowsRegister.queryItem(itemName.c_str(), REG_EXPAND_SZ) ? reinterpret_cast<char*>(windowsRegister.mValueBuffer) : "";
}

template <>
RegNumeric reg_api_a<ctx::os::win>::getValue<RegNumeric>(const RegPath& regPath, const String& itemName)
{
    WindowsRegister windowsRegister(regPath);
    return windowsRegister.queryItem(itemName.c_str(), REG_DWORD) ? *(reinterpret_cast<int*>(windowsRegister.mValueBuffer)) : 0;
}

template <>
RegBoolean reg_api_a<ctx::os::win>::getValue<RegBoolean>(const RegPath& regPath, const String& itemName)
{
    return (getValue<RegNumeric>(regPath, itemName) == 1);
}

template <>
bool reg_api_a<ctx::os::win>::setValue<RegString>(const RegPath& regPath, const String& itemName, const RegString& strValue)
{
    WindowsRegister windowsRegister(regPath);
    DWORD strLen = DWORD(strValue.size());
    if (strLen < WindowsRegister::BUFFER_LEN)
    {
        windowsRegister.mValueLen = strLen;
        strcpy_s(reinterpret_cast<char*>(windowsRegister.mValueBuffer), strValue.length(), strValue.c_str());
    }
    else
    {
        windowsRegister.mValueLen = WindowsRegister::BUFFER_LEN;
        strncpy_s(reinterpret_cast<char*>(windowsRegister.mValueBuffer), strValue.length(), strValue.c_str(), WindowsRegister::BUFFER_LEN);
        windowsRegister.mValueBuffer[WindowsRegister::BUFFER_LEN] = 0;
    }
    return windowsRegister.setItem(itemName.c_str(), REG_EXPAND_SZ);
}

template <>
bool reg_api_a<ctx::os::win>::setValue<RegNumeric>(const RegPath& regPath, const String& itemName, const RegNumeric& numValue)
{
    WindowsRegister windowsRegister(regPath);
    *(reinterpret_cast<DWORD*>(windowsRegister.mValueBuffer)) = DWORD(numValue);
    windowsRegister.mValueLen = sizeof(DWORD);
    return windowsRegister.setItem(itemName.c_str(), REG_DWORD);
}

template <>
bool reg_api_a<ctx::os::win>::setValue<RegBoolean>(const RegPath& regPath, const String& itemName, const RegBoolean& boolValue)
{
    return setValue<RegNumeric>(regPath, itemName, boolValue ? 1 : 0);
}

void reg_api_a<ctx::os::win>::setComponentName(const String& componentName)
{
    WindowsRegister::sComponentName = componentName;
}

reg_api_a<ctx::os::win>::String reg_api_a<ctx::os::win>::componentName()
{
    return WindowsRegister::sComponentName;
}

reg_api_a<ctx::os::win>::String reg_api_a<ctx::os::win>::entryName(const RegPath& regPath, unsigned itemIndex)
{
    return WindowsRegister(regPath).entryName(itemIndex);
}

template <>
String reg_user_domain_a<ctx::os::win>::name()
{
    static constexpr const DWORD BUFFER_LENGTH = 64;
    char userNameBuffer[BUFFER_LENGTH];
    DWORD bufferLength(BUFFER_LENGTH);
    return GetUserNameA(userNameBuffer,&bufferLength) != 0 ? userNameBuffer : "";
}

} // namespace Sy
