
#include "sdk/basics/crypt.h"
#include <ctime>

namespace Sy {

int CryptBase::random()
{
    return std::clock();
}

CryptBase::Char CryptBase::encodeHalf(Byte half)
{
    Byte noise = random() % 4;
    Byte code64 = ((half & 0x0C) << 2) | (noise << 2) | (half & 0x03);

    if (code64 < 10)
    {
        return '0' + code64;
    }
    else if (code64 < 36)
    {
        return 'A' + code64 - 10;
    }
    else if (code64 < 62)
    {
        return 'a' + code64 - 36;
    }
    else
    {
        return code64 == 62 ? '_' : '#';
    }
}

CryptBase::Byte CryptBase::decodeHalf(Char letter)
{
    Byte code64 = 0;
    if (letter == '_')
    {
        code64 = 62;
    }
    else if (letter == '#')
    {
        code64 = 63;
    }
    else if (letter <= '9')
    {
        code64 = (letter - '0');
    }
    else if (letter <= 'Z')
    {
        code64 = (letter - 'A' + 10);
    }
    else if (letter <= 'z')
    {
        code64 = (letter - 'a' + 36);
    }
    return ((code64 & 0x30) >> 2) | (code64 & 0x03);
}

CryptBase::Chunk CryptBase::encodeByte(Byte byteValue)
{
    Byte hiByte = (byteValue >> 4) & 0x0F;
    Byte loByte =  byteValue       & 0x0F;

    Chunk chunk;
    chunk.mBuffer[0] = encodeHalf(hiByte);
    chunk.mBuffer[1] = encodeHalf(loByte);

    return chunk;
}

CryptBase::Chunk CryptBase::encodeByte(const void* baseAddress, Offset offset)
{
    Byte byteValue = *((Byte*)baseAddress + offset) & 0xFF;
    return encodeByte(byteValue);
}

CryptBase::Byte CryptBase::decodeByte(const Chunk& encodedChunk)
{
    Char left = encodedChunk.mBuffer[0];
    Char right = encodedChunk.mBuffer[1];
    Byte hiByte = decodeHalf(left);
    Byte loByte = decodeHalf(right);
    return (hiByte << 4) + loByte;
}

} // namespace Sy
