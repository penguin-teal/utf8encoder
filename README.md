[![Build](https://github.com/penguin-teal/utf8encoder/actions/workflows/Build.yml/badge.svg)](https://github.com/penguin-teal/utf8encoder/actions/workflows/Build.yml)

# utf8encoder
Two simple functions to encode and decode UTF-8 from/to its Unicode code
points using bitwise operators.

## Header

The header file is in `./include/utf8encoder.h`.

```c
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
```

## Building

Build the shared object:
```shell
# Builds ./bin/libutf8encoder.so
make shared
```

Build the static library:
```shell
# Builds ./bin/libutf8encoder.a
make static
```

The default target `make` is the static library.

## Run Tests

Shared object test:
```shell
make sharedtest
```

Static library test:
```shell
make test
```

