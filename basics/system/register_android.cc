
#include "sdk/basics/system/register.h"

namespace Sy {

RegPath reg_api_a<ctx::os::adr>::adminRoot()
{
    return RegPath("");
}

RegPath reg_api_a<ctx::os::adr>::userRoot()
{
    return RegPath("");
}

RegPath reg_api_a<ctx::os::adr>::installStampsRoot()
{
    return RegPath("");
}

bool reg_api_a<ctx::os::adr>::hasItem(const RegPath& regPath, const String& itemName)
{
    return false;
}

template <>
RegString reg_api_a<ctx::os::adr>::getValue<RegString>(const RegPath& regPath, const String& itemName)
{
    return "";
}

template <>
RegNumeric reg_api_a<ctx::os::adr>::getValue<RegNumeric>(const RegPath& regPath, const String& itemName)
{
    return 0;
}

template <>
RegBoolean reg_api_a<ctx::os::adr>::getValue<RegBoolean>(const RegPath& regPath, const String& itemName)
{
    return (getValue<RegNumeric>(regPath, itemName) == 1);
}

template <>
bool reg_api_a<ctx::os::adr>::setValue<RegString>(const RegPath& regPath, const String& itemName, const RegString& strValue)
{
    return false;
}

template <>
bool reg_api_a<ctx::os::adr>::setValue<RegNumeric>(const RegPath& regPath, const String& itemName, const RegNumeric& numValue)
{
    return false;
}

template <>
bool reg_api_a<ctx::os::adr>::setValue<RegBoolean>(const RegPath& regPath, const String& itemName, const RegBoolean& boolValue)
{
    return false;
}

void reg_api_a<ctx::os::adr>::setComponentName(const String& componentName)
{
}

reg_api_a<ctx::os::adr>::String reg_api_a<ctx::os::adr>::componentName()
{
    return "";
}

reg_api_a<ctx::os::adr>::String reg_api_a<ctx::os::adr>::entryName(const RegPath& regPath, unsigned itemIndex)
{
    return "";
}

template <>
String reg_user_domain_a<ctx::os::adr>::name()
{
    return "";
}

} // namespace Sy
