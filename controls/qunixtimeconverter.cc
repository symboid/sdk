
#include "sdk/controls/setup.h"
#include "sdk/controls/qunixtimeconverter.h"
#include <QDateTime>

QUnixTimeConverter::QUnixTimeConverter(QObject* parent) : QObject(parent)
{
}

void QUnixTimeConverter::setYear(int year)
{
    if (mYear != year)
    {
        mYear = year;
        emit yearChanged();
        emit unixTimeChanged();
    }
}

void QUnixTimeConverter::setMonth(int month)
{
    if (mMonth != month)
    {
        mMonth = month;
        emit monthChanged();
        emit unixTimeChanged();
    }
}

void QUnixTimeConverter::setDay(int day)
{
    if (mDay != day)
    {
        mDay = day;
        emit dayChanged();
        emit unixTimeChanged();
    }
}

void QUnixTimeConverter::setHour(int hour)
{
    if (mHour != hour)
    {
        mHour = hour;
        emit hourChanged();
        emit unixTimeChanged();
    }
}

void QUnixTimeConverter::setMinute(int minute)
{
    if (mMinute != minute)
    {
        mMinute = minute;
        emit minuteChanged();
        emit unixTimeChanged();
    }
}

void QUnixTimeConverter::setSecond(int second)
{
    if (mSecond != second)
    {
        mSecond = second;
        emit secondChanged();
        emit unixTimeChanged();
    }
}

qint64 QUnixTimeConverter::unixTime() const
{
    return QDateTime(QDate(mYear,mMonth,mDay), QTime(mHour, mMinute, mSecond)).toSecsSinceEpoch();
}

void QUnixTimeConverter::setUnixTime(qint64 unixTime)
{
    if (this->unixTime() != unixTime)
    {
        QDateTime dateTime;
        dateTime.setSecsSinceEpoch(unixTime);
        QDate date(dateTime.date());
        if (mYear != date.year())
        {
            mYear = date.year();
            emit yearChanged();
        }
        if (mMonth != date.month())
        {
            mMonth = date.month();
            emit monthChanged();
        }
        if (mDay != date.day())
        {
            mDay = date.day();
            emit dayChanged();
        }
        QTime time(dateTime.time());
        if (mHour != time.hour())
        {
            mHour = time.hour();
            emit hourChanged();
        }
        if (mMinute != time.minute())
        {
            mMinute = time.minute();
            emit minuteChanged();
        }
        if (mSecond != time.second())
        {
            mSecond = time.second();
            emit secondChanged();
        }
        emit unixTimeChanged();
    }
}
