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
#ifndef UTF8ENCODER_H
#define UTF8ENCODER_H

#include <stdint.h>
#include <stddef.h>

/**
 * Returns how many bytes the encoded UTF-8 character will take up.
 * This would be the first byte of a multi-byte character.
 * An ASCII character would return 1.
 * @param The first byte of the UTF-8 encoded character.
 * @return How many bytes this encoding takes up from 1 to 4.
 */
size_t utf8Size(uint8_t binary);

/**
 * Encodes a single UTF-8 code point into its binary representation.
 * Fills the `size` argument with the size.
 * `size` will be set to `0` on fail.
 * @param codePoint The code point (e.g. the 0xAE49 in U+AE49).
 * @param size      Where to copy the number of bytes the encoded code
 *                  point uses, or `NULL`.
 * @return The encoded binary, ranging from using 1 to all 4 bytes.
 */
uint32_t utf8Encode(uint64_t codePoint, size_t *size);

/**
 * Decodes a single UTF-8 encoded character into its code point.
 * An error occurred if `binary` was not `0` and this function returns `0`.
 * @param binary The UTF-8 encoded byte character.
 * @return The code point of the UTF-8 encoded character.
 */
uint64_t utf8Decode(uint32_t binary);

#endif

