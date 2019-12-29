
#include "sdk/basics/arccoord.h"
#include <cmath>

namespace Sy {

ArcCoord::ArcCoord(ArcDegree arcPos)
    : mDegree(int(std::floor(arcPos)) % 360)
    , mMinute(0)
    , mSecond(0.0)
{
    double seconds = (arcPos - mDegree) * 3600.0;
    mMinute = int(std::floor(seconds / 60.0));
    mSecond = seconds - mMinute * 60.0;
}

ArcDegree ArcCoord::arcPos() const
{
    return ArcDegree(mDegree) + ArcDegree(mMinute) / 60.0 + ArcDegree(mSecond) / 3600.0;
}

} // namespace Sy
