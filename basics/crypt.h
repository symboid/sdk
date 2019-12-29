
#ifndef __SYMBOID_SDK_BASICS_CRYPT_H__
#define __SYMBOID_SDK_BASICS_CRYPT_H__

#include "ctx/config.h"
#include "sdk/basics/stringutils.h"
#include "sdk/basics/timecalc.h"
#include <cstring>

namespace Sy {

struct CryptBase
{
    typedef unsigned char Byte;
    typedef char Char;
    typedef unsigned Offset;

    static int random();
    static Char encodeHalf(Byte half);
    static Byte decodeHalf(Char letter);

    template <int LENGTH>
    struct chunk_a
    {
        chunk_a(const Char*& buffer, Offset offset = 0)
        {
            std::strncpy(mBuffer, buffer + LENGTH * offset, LENGTH);
            mBuffer[LENGTH] = 0;
        }
        chunk_a()
        {
            std::memset(mBuffer, 0, LENGTH + 1);
        }
        Char mBuffer[LENGTH + 1];
    };
    typedef chunk_a<2> Chunk;
    static Chunk encodeByte(Byte byteValue);
    static Chunk encodeByte(const void* baseAddress, Offset offset);
    static Byte decodeByte(const Chunk& integerChunk);
};

template <class _ctx_string>
struct crypt_a : CryptBase
{
    typedef string_a<_ctx_string> String;

    template <typename Type>
    static String encode(const Type& value)
    {
        String timeString;
        const void* address = reinterpret_cast<const void*>(&value);
        for (Offset offset = 0; offset < sizeof(Type); ++offset)
        {
            const Chunk chunk = encodeByte(address, offset);
            timeString += String(chunk.mBuffer);
        }
        return timeString;
    }

    template <typename Type>
    static void decode(const String& encodedStr, Type& value)
    {
        const std::string encodedStrStd(encodedStr.std());
        Byte* valueAddress = reinterpret_cast<Byte*>(&value);
        Offset strLen = Offset(encodedStrStd.size());
        const Char* strAddr(encodedStrStd.c_str());
        for (Offset offset = 0; offset < sizeof(Type); ++offset)
        {
            Byte byteValue = 0;
            if ((2 * offset + 1) < strLen)
            {
                byteValue = decodeByte(Chunk(strAddr, offset));
            }
            valueAddress[offset] = byteValue;
        }
    }

    template <typename Type>
    static Type decode(const String& encodedStr)
    {
        Type value;
        decode<Type>(encodedStr, value);
        return value;
    }

    static String encodeString(const String& strValue)
    {
        String encodedStr;
        const std::string strStd(strValue.std());
        const typename String::Char* buffer = strStd.c_str();
        for (typename String::Pos pos = 0, len = strValue.size(); pos < len; ++pos)
        {
            const Chunk chunk = encodeByte(buffer, pos);
            encodedStr += String(chunk.mBuffer);
        }
        return encodedStr;
    }

    static String decodeString(const String& encodedStr)
    {
        const std::string encodedStrStd(encodedStr.std());
        const Char* strAddr(encodedStrStd.c_str());
        String strValue;
        for (Offset offset = 0, len = encodedStrStd.size() / 2; offset < len; ++offset)
        {
            const Byte charByte = decodeByte(Chunk(strAddr, offset));
            strValue += String((const Sy::String::Char*)(&charByte), 1);
        }
        return strValue;
    }
};

typedef crypt_a<ctx::string> Crypt;

template <class _ctx_string>
struct start_token_a : crypt_a<_ctx_string>::String
{
    start_token_a(const Sy::String& appShortId)
    {
        // resolving current date:
        Time currentDate = Time::currentDate();

        // encoding current date:
        (*this) += crypt_a<_ctx_string>::encode(currentDate.mDay);
        (*this) += crypt_a<_ctx_string>::encode(currentDate.mMonth);
        (*this) += crypt_a<_ctx_string>::encode(currentDate.mYear);

        // encoding app short id:
        (*this) += crypt_a<_ctx_string>::encodeString(appShortId);
    }

    bool check(const start_token_a<_ctx_string>& rhs, const Sy::String& appShortId) const
    {
        unsigned monthPos = 2 * sizeof(int);
        unsigned yearPos = monthPos + 2 * sizeof(int);
        unsigned idPos = yearPos + 2 * sizeof(int);
        int decodedDay = crypt_a<_ctx_string>::template decode<int>(rhs.left(monthPos));
        int decodedMonth = crypt_a<_ctx_string>::template decode<int>(rhs.mid(monthPos, yearPos - monthPos));
        int decodedYear = crypt_a<_ctx_string>::template decode<int>(rhs.mid(yearPos, idPos - yearPos));
        Sy::String decodedId = crypt_a<_ctx_string>::decodeString(rhs.mid(idPos));

        Time currentDate = Time::currentDate();

        return (currentDate.mYear == decodedYear) && (currentDate.mMonth = decodedMonth) &&
                (currentDate.mDay == decodedDay) && (appShortId == decodedId);
    }
};

typedef start_token_a<ctx::string> StartToken;

template <class _ctx_string>
struct install_stamp_a
{
    install_stamp_a()
        : mEncodedStamp(crypt_a<_ctx_string>::encode(UnixTime::now()))
    {
    }
        install_stamp_a(const typename crypt_a<_ctx_string>::String& encodedStamp)
        : mEncodedStamp(encodedStamp)
    {
    }

    typename crypt_a<_ctx_string>::String mEncodedStamp;

    int trialDaysLeft(int maxTrialDays) const
    {
        UnixTime::Type installTime = Crypt::decode<UnixTime::Type>(mEncodedStamp);
        int daysSinceInstall = (UnixTime::now() - installTime) / UnixTime::DAY_LENGTH;
        return maxTrialDays > daysSinceInstall ? maxTrialDays - daysSinceInstall : 0;
    }

};

typedef install_stamp_a<ctx::string> InstallStamp;

} // namespace Sy

#endif // __SYMBOID_SDK_BASICS_CRYPT_H__
