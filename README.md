[![Build](https://github.com/penguin-teal/utf8encoder/actions/workflows/Build.yml/badge.svg)](https://github.com/penguin-teal/utf8encoder/actions/workflows/Build.yml)

# utf8encoder
Two simple functions to encode and decode UTF-8 from/to its Unicode code
points using bitwise operators. A third function to get the size of a
UTF-8 character from its first byte.

The Makefile is for Linux, however the code itself should compile on any
platform.

## Header

The header file is in `./include/utf8encoder.h`.

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

