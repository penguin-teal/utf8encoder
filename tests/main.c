#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "utf8encoder.h"

int main()
{
    bool success = true;

    uint64_t codePoint;
    uint32_t binary;
    size_t size;

    // Test utf8Encode

    codePoint = 0x24; // $
    binary = utf8Encode(codePoint, &size);
    if(binary != 0x24 || size != 1)
    {
        fprintf(stderr, "Error: Dollar U+0024 encoded to 0x%X (%lu bytes), not 0x24 (1 byte).\n", binary, size);
        success = false;
    }

    codePoint = 0xA3; // Pound
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xC2A3 || size != 2)
    {
        fprintf(stderr, "Error: Pound U+00A3 encoded to 0x%X (%lu bytes), not 0xC2A3 (2 bytes).\n", binary, size);
        success = false;
    }

    codePoint = 0x0418; // Cyrillic I
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xD098 || size != 2)
    {
        fprintf(stderr, "Error: Cyrillic I U+0418 encoded to 0x%X (%lu bytes), not 0xD098 (2 bytes).\n", binary, size);
        success = false;
    }
    
    codePoint = 0x20AC; // Euro
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xE282ACu || size != 3)
    {
        fprintf(stderr, "Error: Euro U+20AC encoded to 0x%X (%lu bytes), not 0xE282AC (3 bytes).\n", binary, size);
        success = false;
    }

    codePoint = 0x10348u; // Hwair
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xF0908D88u || size != 4)
    {
        fprintf(stderr, "Error: Hwair U+10348 encoded to 0x%X (%lu bytes), not 0xF0908D88 (4 bytes).\n", binary, size);
        success = false;
    }

    // Test utf8Decode

    binary = 0x24; // $
    codePoint = utf8Decode(binary);
    if(codePoint != 0x24)
    {
        fprintf(stderr, "Error: Dollar binary 0x24 decoded to U+%lX, not U+0024.\n", codePoint);
        success = false;
    }

    binary = 0xC2A3; // Pound
    codePoint = utf8Decode(binary);
    if(codePoint != 0xA3)
    {
        fprintf(stderr, "Error: Pound binary 0xC2A3 decoded to U+%lX, not U+00A3.\n", codePoint);
        success = false;
    }

    binary = 0xD098; // Cyrillic I
    codePoint = utf8Decode(binary);
    if(codePoint != 0x0418)
    {
        fprintf(stderr, "Error: Cyrillic I binary 0xD098 decoded to U+%lX, not U+0418.\n", codePoint);
        success = false;
    }

    binary = 0xE282ACu; // Euro
    codePoint = utf8Decode(binary);
    if(codePoint != 0x20AC)
    {
        fprintf(stderr, "Error: Euro binary 0xE282AC decoded to U+%lX, not U+20AC.\n", codePoint);
        success = false;
    }

    binary = 0xF0908D88u; // Hwair
    codePoint = utf8Decode(binary);
    if(codePoint != 0x10348u)
    {
        fprintf(stderr, "Error: Hwair binary 0xF0908D88 decoded to U+%lX, not U+10348.\n", codePoint);
        success = false;
    }

    // Test utf8Size

    size = utf8Size(0x24); // $
    if(size != 1)
    {
        fprintf(stderr, "Error: Dollar binary 0x24 said to be of size %lu, not 1.\n", size);
    }

    size = utf8Size(0xC2); // Pound
    if(size != 2)
    {
        fprintf(stderr, "Error: Pound binary 0xC2-- said to be of size %lu, not 2.\n", size);
    }

    size = utf8Size(0xD0); // Cyrillic I
    if(size != 2)
    {
        fprintf(stderr, "Error: Cyrillic I binary 0xD0-- said to be of size %lu, not 2.\n", size);
    }

    size = utf8Size(0xE2); // Euro
    if(size != 3)
    {
        fprintf(stderr, "Error: Euro binary 0xE2---- said to be of size %lu, not 3.\n", size);
    }

    size = utf8Size(0xF0); // Hwair
    if(size != 4)
    {
        fprintf(stderr, "Error: Euro binary 0xF0------ said to be of size %lu, not 4.", size);
    }

    if(success)
    {
        printf("Test succeeded!\n");
        return 0;
    }
    else
    {
        printf("Test failed.\n");
        return 1;
    }
}

