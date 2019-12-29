
#ifndef __SYMBOID_SDK_BASICS_SYSTEM_REGISTER_H__
#define __SYMBOID_SDK_BASICS_SYSTEM_REGISTER_H__

#include "ctx/config.h"
#include "sdk/basics/stringutils.h"
#include "sdk/basics/path.h"
#include "sdk/basics/os.h"

namespace Sy {

typedef string_a<ctx::types::std_string> RegString;
typedef long RegNumeric;
typedef bool RegBoolean;

struct RegPath
{
    typedef path_a<ctx::types::std_string, ctx::os::current::dirsep> EntryPath;

    RegPath(const EntryPath& rootPath, const EntryPath& entryPath = "")
        : mRootPath(rootPath)
        , mEntryPath(entryPath)
    {
    }

    EntryPath mRootPath;
    EntryPath mEntryPath;

    RegPath operator / (const RegString& itemName)
    {
        return RegPath(mRootPath, mEntryPath / itemName);
    }
};

template <class _ctx_os>
struct reg_api_a;

template <>
struct reg_api_a<ctx::os::win>
{
    typedef string_a<ctx::types::std_string> String;

    static RegPath adminRoot();
    static RegPath userRoot();
    static RegPath installStampsRoot();

    static bool hasItem(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static RegValue getValue(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static bool setValue(const RegPath& entryPath, const String& itemName, const RegValue& strValue);

    static void setComponentName(const String& componentName);
    static String componentName();

    static String entryName(const RegPath& regPath, unsigned itemIndex);
};

template <>
struct reg_api_a<ctx::os::mac>
{
    typedef string_a<ctx::types::std_string> String;

    static RegPath adminRoot();
    static RegPath userRoot();
    static RegPath installStampsRoot();

    static bool hasItem(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static RegValue getValue(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static bool setValue(const RegPath& entryPath, const String& itemName, const RegValue& strValue);

    static void setComponentName(const String& componentName);
    static String componentName();

    static String entryName(const RegPath& regPath, unsigned itemIndex);
};

template <>
struct reg_api_a<ctx::os::lin>
{
    typedef string_a<ctx::types::std_string> String;

    static RegPath adminRoot();
    static RegPath userRoot();
    static RegPath installStampsRoot();

    static bool hasItem(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static RegValue getValue(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static bool setValue(const RegPath& entryPath, const String& itemName, const RegValue& strValue);

    static void setComponentName(const String& componentName);
    static String componentName();

    static String entryName(const RegPath& regPath, unsigned itemIndex);
};

template <>
struct reg_api_a<ctx::os::adr>
{
    typedef string_a<ctx::types::std_string> String;

    static RegPath adminRoot();
    static RegPath userRoot();
    static RegPath installStampsRoot();

    static bool hasItem(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static RegValue getValue(const RegPath& entryPath, const String& itemName);

    template <typename RegValue>
    static bool setValue(const RegPath& entryPath, const String& itemName, const RegValue& strValue);

    static void setComponentName(const String& componentName);
    static String componentName();

    static String entryName(const RegPath& regPath, unsigned itemIndex);
};

template <class RegEntry, class RegItem>
struct RegEntryCat
{
    typedef typename RegEntry::Api Api;
    static RegPath path() { return RegEntry::path() / RegItem::name(); }
};

template <class _ctx_os>
struct reg_component_domain_a
{
    static void setName(const String& componentName)
    {
        reg_api_a<_ctx_os>::setComponentName(componentName);
    }
    static String name() { return reg_api_a<_ctx_os>::componentName(); }
};

typedef reg_component_domain_a<ctx::os::current> RegComponent;

template <class _ctx_os>
struct reg_user_domain_a
{
    static String name();
};

template <class _ctx_os>
struct reg_root_admin_a
{
    typedef reg_api_a<_ctx_os> Api;

    typedef RegEntryCat<reg_root_admin_a<_ctx_os>, reg_component_domain_a<_ctx_os>> ComponentEntry;
    typedef RegEntryCat<ComponentEntry, reg_user_domain_a<_ctx_os>> UserEntry;

    static RegPath path()
    {
        return Api::adminRoot();
    }
};

template <class _ctx_os>
struct reg_root_user_a
{
    typedef reg_api_a<_ctx_os> Api;

    typedef RegEntryCat<reg_root_user_a<_ctx_os>, reg_component_domain_a<_ctx_os>> ComponentEntry;
    typedef ComponentEntry UserEntry;

    static RegPath path()
    {
        return Api::userRoot();
    }
};

template <class _ctx_os>
struct reg_root_install_stamps_a
{
    typedef reg_api_a<_ctx_os> Api;

    typedef RegEntryCat<reg_root_install_stamps_a<_ctx_os>, reg_component_domain_a<_ctx_os>> ComponentEntry;
    typedef RegEntryCat<ComponentEntry, reg_user_domain_a<_ctx_os>> UserEntry;

    static RegPath path()
    {
        return Api::installStampsRoot();
    }
};

template <class RegEntry, class RegItem, typename RegValue>
struct RegValueItem
{
    typedef typename RegEntry::Api Api;

    static bool exists()
    {
        return Api::hasItem(RegEntry::path(), RegItem::name);
    }
    static bool set(const RegValue& value)
    {
        return Api::setValue(RegEntry::path(), RegItem::name, value);
    }
    static RegValue get()
    {
        return Api::template getValue<RegValue>(RegEntry::path(), RegItem::name);
    }
};

template <class RegEntry, class RegItem> struct RegStringItem : RegValueItem<RegEntry,RegItem,RegString> {};
template <class RegEntry, class RegItem> struct RegNumericItem : RegValueItem<RegEntry,RegItem,RegNumeric> {};
template <class RegEntry, class RegItem> struct RegBooleanItem : RegValueItem<RegEntry,RegItem,RegBoolean> {};

template<class _ctx_os, template <class> class RegRoot>
struct reg_a
{
    typedef typename RegRoot<_ctx_os>::ComponentEntry ComponentEntry;
    struct install_dir : RegStringItem<ComponentEntry,install_dir>
    {
        static constexpr const char* name = "install_dir";
    };
    struct install_stamp : RegStringItem<ComponentEntry,install_stamp>
    {
        static constexpr const char* name = "install_stamp";
    };

    typedef typename RegRoot<_ctx_os>::UserEntry UserEntry;
    struct eula_version : RegNumericItem<UserEntry,eula_version>
    {
        static constexpr const char* name = "eula_version";
    };

    static int sComponentIndex;

    static void componentLoopInit()
    {
        sComponentIndex = 0;
    }

    static bool componentLoopStep()
    {
        RegPath rootPath = RegRoot<_ctx_os>::path();
        RegString componentName = RegRoot<_ctx_os>::Api::entryName(rootPath, sComponentIndex++);
        reg_component_domain_a<_ctx_os>::setName(componentName);
        return (componentName != "");
    }
};

template<class _ctx_os, template <class> class RegRoot>
int reg_a<_ctx_os,RegRoot>::sComponentIndex(0);

typedef reg_a<ctx::os::current, reg_root_admin_a> RegAdmin;

typedef reg_a<ctx::os::current, reg_root_user_a> RegUser;

typedef reg_a<ctx::os::current, reg_root_install_stamps_a> RegInstallStamps;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_SYSTEM_REGISTER_H__
