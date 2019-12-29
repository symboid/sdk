
#ifndef __SYMBOID_SDK_BASICS_TIMECALC_H__
#define __SYMBOID_SDK_BASICS_TIMECALC_H__

#include "ctx/config.h"
#include <ctime>

namespace Sy {

struct UnixTime
{
    typedef std::time_t Type;
    static Type now();
    static constexpr const Type DAY_LENGTH = 86400;
};

template <typename ScalarTime>
struct time_a
{
    typedef int Year;
    typedef int Month;
    typedef int Day;
    typedef int Hour;
    typedef int Minute;
    typedef int Second;

    Year mYear;
    Month mMonth;
    Day mDay;
    Hour mHour;
    Minute mMin;
    Second mSec;

    typedef typename ScalarTime::Type ScalarType;
    void fromScalar(ScalarType scalarTime);
    ScalarType toScalar() const;

    time_a(Year year, Month month, Day day, Hour hour = 0, Minute minute = 0, Second second = 0)
        : mYear(year)
        , mMonth(month)
        , mDay(day)
        , mHour(hour)
        , mMin(minute)
        , mSec(second)
    {
    }

    time_a(ScalarType scalarTime = ScalarType(0))
        : mYear(0)
        , mMonth(0)
        , mDay(0)
        , mHour(0)
        , mMin(0)
        , mSec(0)
    {
        fromScalar(scalarTime);
    }

    template<class OtherTime>
    time_a<OtherTime> toTime() const
    {
        return time_a<OtherTime>(mYear, mMonth, mDay, mHour, mMin, mSec);
    }

    time_a& add(ScalarType diffTime, ScalarType diffUnit = ScalarType(1))
    {
        fromScalar(toScalar() + (diffTime * ScalarTime::DAY_LENGTH / diffUnit));
        return *this;
    }

    time_a addYears(Year yearCount) const
    {
        time_a incrementedTime(*this);
        incrementedTime.mYear += yearCount;
        return incrementedTime;
    }
    time_a addDays(Day days) const
    {
        time_a incrementedTime(*this);
        incrementedTime.add(ScalarType(days), 1);
        return incrementedTime;
    }
    time_a addHours(Hour hours) const
    {
        time_a incrementedTime(*this);
        incrementedTime.add(ScalarType(hours), 24);
        return incrementedTime;
    }
    time_a addMins(Minute mins) const
    {
        time_a incrementedTime(*this);
        incrementedTime.add(ScalarType(mins), 1440);
        return incrementedTime;
    }

    static time_a current()
    {
        return time_a(ScalarTime::now());
    }
    static time_a currentDate()
    {
        time_a currentTime = current();
        currentTime.mHour = 0;
        currentTime.mMin = 0;
        currentTime.mSec = 0;
        return currentTime;
    }
};

typedef time_a<UnixTime> Time;

template<>
void time_a<UnixTime>::fromScalar(UnixTime::Type unixTime);

template<>
UnixTime::Type time_a<UnixTime>::toScalar() const;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_TIMECALC_H__
