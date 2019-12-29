
#ifndef __SYMBOID_SDK_BASICS_MEMORY_H__
#define __SYMBOID_SDK_BASICS_MEMORY_H__

#include "sdk/basics/defs.h"

namespace Sy {

template <class Class>
class ScopePtr
{
public:
    ScopePtr(Class* object) : mObject(object) {}
    ~ScopePtr() { delete mObject; }
private:
    Class* mObject;
public:
    Class* operator->() { return mObject; }
    const Class* operator->() const { return mObject; }
    Class& operator*() { return *mObject; }
    const Class& operator*() const { return *mObject; }
    bool isNull() const { return !mObject; }
    void reset(Class* object) { delete mObject; mObject = object; }
};

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_MEMORY_H__
