
#include "sdk/basics/system/register.h"
#import <Foundation/Foundation.h>

namespace Sy {

struct PlistFileRegister
{
    PlistFileRegister(const RegPath& regPath);

    NSURL* mRootPath;
    NSMutableDictionary<NSString*,id>* mRootDomain;
    NSMutableDictionary<NSString*,id>* mDomain;

    NSString* getValue(const String& itemName) const;

    template <typename Value>
    bool setValue(const String& itemName, Value value);

    static reg_api_a<ctx::os::mac>::String sComponentName;
};

PlistFileRegister::PlistFileRegister(const RegPath& regPath)
{
    // path of plist file:
    String rootPathStr = regPath.mRootPath.toString();
    NSString* plistPath = [[NSString alloc] initWithUTF8String:rootPathStr.c_str()];
    mRootPath = [[NSURL alloc] initFileURLWithPath:plistPath];

    // creating root domain by loading the plist file from root path:
    mRootDomain = [NSMutableDictionary dictionaryWithContentsOfURL:mRootPath];
    // without existing plist file en empty root domain is created:
    if (mRootDomain == nil)
    {
        mRootDomain = [[NSMutableDictionary alloc] init];
    }

    // ensuring sub domain inside the root domain:
    mDomain = mRootDomain;
    //QStringList subDomainNames = subDomainPath.split('/', QString::SkipEmptyParts);
    StringList subDomainNames = regPath.mEntryPath;
    for (String subDomainNameStr : subDomainNames)
    {
        NSString* subDomainName = [NSString stringWithUTF8String:subDomainNameStr.c_str()];
        NSMutableDictionary* subDomain = [mDomain valueForKey:subDomainName];
        if (subDomain == nil)
        {
            subDomain = [[NSMutableDictionary alloc] init];
            [mDomain setValue:subDomain forKey:subDomainName];
        }
        mDomain = subDomain;
    }
}

NSString* PlistFileRegister::getValue(const String& itemName) const
{
    NSString* itemKey = [NSString stringWithUTF8String:itemName.c_str()];
    return [mDomain valueForKey:itemKey];
}

template <typename Value>
bool PlistFileRegister::setValue(const String& itemName, Value value)
{
    NSString* itemKey = [NSString stringWithUTF8String:itemName.c_str()];
    [mDomain setValue:value forKey:itemKey];
    return [mRootDomain writeToURL:mRootPath atomically:YES];
}

reg_api_a<ctx::os::mac>::String PlistFileRegister::sComponentName;

RegPath reg_api_a<ctx::os::mac>::adminRoot()
{
    return RegPath("/Library/Symboid/System.plist");
}

RegPath reg_api_a<ctx::os::mac>::userRoot()
{
    return RegPath::EntryPath(Os::getenv("HOME")) / ".symboid/System.plist";
}

RegPath reg_api_a<ctx::os::mac>::installStampsRoot()
{
    return reg_api_a<ctx::os::mac>::adminRoot();
}

bool reg_api_a<ctx::os::mac>::hasItem(const RegPath& regPath, const String& itemName)
{
    PlistFileRegister fileRegister(regPath);
    NSString* valueKey = [NSString stringWithUTF8String:itemName.c_str()];
    return [[fileRegister.mDomain allKeys] containsObject:valueKey] == YES;
}

template <>
RegString reg_api_a<ctx::os::mac>::getValue<RegString>(const RegPath& regPath, const String& itemName)
{
    NSString* strValue = PlistFileRegister(regPath).getValue(itemName);
    return String(strValue != nil ? [strValue UTF8String] : "");
}

template <>
RegNumeric reg_api_a<ctx::os::mac>::getValue<RegNumeric>(const RegPath& regPath, const String& itemName)
{
    return [PlistFileRegister(regPath).getValue(itemName) integerValue];
}

template <>
RegBoolean reg_api_a<ctx::os::mac>::getValue<RegBoolean>(const RegPath& regPath, const String& itemName)
{
    return [PlistFileRegister(regPath).getValue(itemName) boolValue];
}

template <>
bool reg_api_a<ctx::os::mac>::setValue<RegString>(const RegPath& regPath, const String& itemName, const RegString& strValue)
{
    return PlistFileRegister(regPath).setValue(itemName, [NSString stringWithUTF8String:strValue.c_str()]);
}

template <>
bool reg_api_a<ctx::os::mac>::setValue<RegNumeric>(const RegPath& regPath, const String& itemName, const RegNumeric& numValue)
{
    return PlistFileRegister(regPath).setValue(itemName, [NSNumber numberWithLong:numValue]);
}

template <>
bool reg_api_a<ctx::os::mac>::setValue<RegBoolean>(const RegPath& regPath, const String& itemName, const RegBoolean& boolValue)
{
    return PlistFileRegister(regPath).setValue(itemName, [NSNumber numberWithBool:boolValue]);
}

void reg_api_a<ctx::os::mac>::setComponentName(const String& componentName)
{
    PlistFileRegister::sComponentName = componentName;
}

reg_api_a<ctx::os::mac>::String reg_api_a<ctx::os::mac>::componentName()
{
    return PlistFileRegister::sComponentName;
}

reg_api_a<ctx::os::mac>::String reg_api_a<ctx::os::mac>::entryName(const RegPath& regPath, unsigned itemIndex)
{
    PlistFileRegister fileRegister(regPath);
    NSArray<NSString*>* itemKeys = [fileRegister.mDomain allKeys];
    if (itemIndex < [itemKeys count])
    {
        NSString* key = itemKeys[itemIndex];
        return  String([key UTF8String]);
    }
    else
    {
        return "";
    }

}

template <>
String reg_user_domain_a<ctx::os::mac>::name()
{
    NSString* userName = NSUserName();
    return String([userName UTF8String]);
}

} // namespace Sy
