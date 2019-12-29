
#include "sdk/basics/timecalc.h"
#include <cstring>

namespace Sy {

UnixTime::Type UnixTime::now()
{
    return std::time(nullptr);
}

template<>
void time_a<UnixTime>::fromScalar(UnixTime::Type unixTime)
{
    const struct std::tm* tmPacked = std::localtime(&unixTime);
    if (tmPacked)
    {
        mYear = tmPacked->tm_year + 1900;
        mMonth = tmPacked->tm_mon + 1;
        mDay = tmPacked->tm_mday;
        mHour = tmPacked->tm_hour;
        mMin = tmPacked->tm_min;
        mSec = tmPacked->tm_sec;
    }
}

template<>
UnixTime::Type time_a<UnixTime>::toScalar() const
{
    struct std::tm tmPacked;
    std::memset(&tmPacked, 0, sizeof(tmPacked));
    tmPacked.tm_year = mYear - 1900;
    tmPacked.tm_mon = mMonth - 1;
    tmPacked.tm_mday = mDay;
    tmPacked.tm_hour = mHour;
    tmPacked.tm_min = mMin;
    tmPacked.tm_sec = mSec;
    tmPacked.tm_isdst = -1;
    return std::mktime(&tmPacked);
}

} // namespace Sy
