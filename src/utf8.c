/*
 * This file is part of Utf8encoder.

 * Utf8encoder is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.

 * Utf8encoder is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.

 * You should have received a copy of the GNU General Public License along with
 * Utf8encoder. If not, see <https://www.gnu.org/licenses/>. 
 */
#include <stdint.h>
#include <stddef.h>

/**
 * Returns how many bytes the encoded UTF-8 character will take up.
 * This would be the first byte of a multi-byte character.
 * An ASCII character would return 1.
 * @param The first byte of the UTF-8 encoded character.
 * @return How many bytes this encoding takes up from 1 to 4.
 */
size_t utf8Size(uint8_t binary)
{
    if((binary >> 3 & 0b11111) == 0b11110)
    {
        return 4;
    }
    else if((binary >> 4 & 0b1111) == 0b1110)
    {
        return 3;
    }
    else if((binary >> 5 & 0b111) == 0b110)
    {
        return 2;
    }
    else if((binary >> 7 & 0b1) == 0)
    {
        return 1;
    }
    else return 0;
}

/**
 * Encodes a single UTF-8 code point into its binary representation.
 * Fills the `size` argument with the size.
 * `size` will be set to `0` on fail.
 * @param codePoint The code point (e.g. the 0xAE49 in U+AE49).
 * @param size      Where to copy the number of bytes the encoded code
 *                  point uses, or `NULL`.
 * @return The encoded binary, ranging from using 1 to all 4 bytes.
 */
uint32_t utf8Encode(uint64_t codePoint, size_t *size)
{
    // Is the code point ASCII?
    if(codePoint <= 0x007Fu)
    {
        // ASCII characters are 1 byte
        if(size) *size = 1;
        // Then just return the code point (the first bit will already be 0).
        return codePoint;
    }
    // Between U+0080 and U+07FF?
    else if(codePoint <= 0x07FFu)
    {
        // This range is encoded in 2 bytes
        if(size) *size = 2;
        // Put 5 highest bits '110xxxxx'
        uint8_t byte1 = 0b11000000 | codePoint >> 6;
        // Rest of bits in '10xxxxxx'
        uint8_t byte2 = 0b10000000 | (0b00111111 & codePoint);
        // Arrange the bits in the uint32 correctly
        return (uint32_t)byte1 << 8 | (uint32_t)byte2;
    }
    // Between U+0800 and U+FFFF?
    else if(codePoint <= 0xFFFFu)
    {
        // This range is encoded in 3 bytes
        if(size) *size = 3;
        // Put 4 highest bits in '1110xxxx'
        uint8_t byte1 = 0b11100000 | codePoint >> 12;
        // Next 6 bytes in '10xxxxxx'
        uint8_t byte2 = 0b10000000 | (0b00111111 & codePoint >> 6);
        // Next 6 bytes in '10xxxxxx'
        uint8_t byte3 = 0b10000000 | (0b00111111 & codePoint);
        // Arrange the bits in the uint32 correctly
        return (uint32_t)byte1 << 16 | (uint32_t)byte2 << 8 | byte3;
    }
    // Between U+10000 and U+10FFFF?
    else if(codePoint <= 0x10FFFFu)
    {
        // This range is encoded in 4 bytes
        if(size) *size = 4;
        // Put 3 highest bits in '11110xxx'
        uint8_t byte1 = 0b11110000 | codePoint >> 18;
        // Next 6 bytes in '10xxxxxx'
        uint8_t byte2 = 0b10000000 | (0b00111111 & codePoint >> 12);
        // Next 6 bytes in '10xxxxxx'
        uint8_t byte3 = 0b10000000 | (0b00111111 & codePoint >> 6);
        // Next 6 bytes in '10xxxxxx'
        uint8_t byte4 = 0b10000000 | (0b00111111 & codePoint);
        // Arrange the bits in the uint32 correctly
        return (uint32_t)byte1 << 24 | (uint32_t)byte2 << 16 | (uint32_t)byte3 << 8 | byte4;
    }
    else
    {
        // Set size to 0 on fail
        if(size) *size = 0;
        // Note that if 0 is returned and codePoint is not 0 this also
        // indicates a failure
        return 0;
    }
}

/**
 * Decodes a single UTF-8 encoded character into its code point.
 * An error occurred if `binary` was not `0` and this function returns `0`.
 * @param binary The UTF-8 encoded byte character.
 * @return The code point of the UTF-8 encoded character.
 */
uint64_t utf8Decode(uint32_t binary)
{
    // Does most significant byte start with '11110'?
    if((binary >> (24 + 3) & 0b11111) == 0b11110)
    {
        // Lowest 6 bits
        uint8_t last6   = binary       & 0b00111111;
        // Next lowest 6 bits
        uint8_t second6 = binary >> 8  & 0b00111111;
        // Next lowest 6 bits
        uint8_t first6  = binary >> 16 & 0b00111111;
        // Highest 3 bits
        uint8_t sig3    = binary >> 24 & 0b00000111;
        // Arrange bits into a code point
        return (uint64_t)sig3 << 15 | (uint64_t)first6 << 12 | (uint64_t)second6 << 6 | last6;
    }
    // Does 2nd most significant byte start with '1110'?
    else if((binary >> (16 + 4) & 0b1111) == 0b1110)
    {
        // Lowest 6 bits
        uint8_t last6   = binary       & 0b00111111;
        // Next lowest 6 bits
        uint8_t next6   = binary >> 8  & 0b00111111;
        // Highest 4 bits
        uint8_t sig4    = binary >> 16 & 0b00001111;
        return (uint64_t)sig4 << 12 | (uint64_t)next6 << 6 | last6;
    }
    // Does 3rd most significant byte start with '110'?
    else if((binary >> (8 + 5) & 0b111) == 0b110)
    {
        // Lowest 6 bits
        uint8_t last6   = binary       & 0b00111111;
        // Highest 4 bits
        uint8_t sig5    = binary >> 8  & 0b00011111;
        return (uint64_t)sig5 << 6 | last6;
    }
    // Does the last byte start with '0'?
    else if((binary >> 7 & 0b1) == 0)
    {
        // ASCII characters are the same encoded as their code points
        return binary;
    }
    // If none of the above applied the binary is invalid
    else
    {
        // If 0 is returned and the input is not 0 then an error occurred
        return 0;
    }
}

