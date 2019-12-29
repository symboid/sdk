
#include "sdk/basics/system/register.h"

namespace Sy {

RegPath reg_api_a<ctx::os::lin>::adminRoot()
{
    return RegPath("");
}

RegPath reg_api_a<ctx::os::lin>::userRoot()
{
    return RegPath("");
}

RegPath reg_api_a<ctx::os::lin>::installStampsRoot()
{
    return RegPath("");
}

bool reg_api_a<ctx::os::lin>::hasItem(const RegPath& regPath, const String& itemName)
{
    return false;
}

template <>
RegString reg_api_a<ctx::os::lin>::getValue<RegString>(const RegPath& regPath, const String& itemName)
{
    return "";
}

template <>
RegNumeric reg_api_a<ctx::os::lin>::getValue<RegNumeric>(const RegPath& regPath, const String& itemName)
{
    return 0;
}

template <>
RegBoolean reg_api_a<ctx::os::lin>::getValue<RegBoolean>(const RegPath& regPath, const String& itemName)
{
    return (getValue<RegNumeric>(regPath, itemName) == 1);
}

template <>
bool reg_api_a<ctx::os::lin>::setValue<RegString>(const RegPath& regPath, const String& itemName, const RegString& strValue)
{
    return false;
}

template <>
bool reg_api_a<ctx::os::lin>::setValue<RegNumeric>(const RegPath& regPath, const String& itemName, const RegNumeric& numValue)
{
    return false;
}

template <>
bool reg_api_a<ctx::os::lin>::setValue<RegBoolean>(const RegPath& regPath, const String& itemName, const RegBoolean& boolValue)
{
    return false;
}

void reg_api_a<ctx::os::lin>::setComponentName(const String& componentName)
{
}

reg_api_a<ctx::os::lin>::String reg_api_a<ctx::os::lin>::componentName()
{
    return "";
}

reg_api_a<ctx::os::lin>::String reg_api_a<ctx::os::lin>::entryName(const RegPath& regPath, unsigned itemIndex)
{
    return "";
}

template <>
String reg_user_domain_a<ctx::os::lin>::name()
{
    return "";
}

} // namespace Sy
