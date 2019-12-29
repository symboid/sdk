
#ifndef __SYMBOID_SDK_BASICS_ARCCOORD_H__
#define __SYMBOID_SDK_BASICS_ARCCOORD_H__

#include "sdk/basics/defs.h"

namespace Sy {

typedef double ArcDegree;

struct SY_API_EXPORT ArcCoord
{
    typedef int Degree;
    typedef int Minute;
    typedef ArcDegree Second;

    ArcCoord(ArcDegree arcPos);

    Degree mDegree;
    Minute mMinute;
    Second mSecond;

    ArcDegree arcPos() const;
};

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_ARCCOORD_H__
