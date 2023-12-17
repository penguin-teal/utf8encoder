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

    codePoint = 0x24; // $
    binary = utf8Encode(codePoint, &size);
    if(binary != 0x24 || size != 1)
    {
        fprintf(stderr, "Error: Dollar U+0024 encoded to 0x%X (%lu bytes)\n", binary, size);
        success = false;
    }

    codePoint = 0xA3; // Pound
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xC2A3 || size != 2)
    {
        fprintf(stderr, "Error: Pound U+00A3 encoded to 0x%X (%lu bytes)\n", binary, size);
        success = false;
    }

    codePoint = 0x0418; // Cyrillic I
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xD098 || size != 2)
    {
        fprintf(stderr, "Error: Cyrillic I U+0418 encoded to 0x%X (%lu bytes)\n", binary, size);
        success = false;
    }
    
    codePoint = 0x20AC; // Euro
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xE282ACu || size != 3)
    {
        fprintf(stderr, "Error: Euro U+20AC encoded to 0x%X (%lu bytes)\n", binary, size);
        success = false;
    }

    codePoint = 0x10348u; // Hwair
    binary = utf8Encode(codePoint, &size);
    if(binary != 0xF0908D88u || size != 4)
    {
        fprintf(stderr, "Error: Hwair U+10348 encoded to 0x%X (%lu bytes)\n", binary, size);
        success = false;
    }

    binary = 0x24; // $
    codePoint = utf8Decode(binary);
    if(codePoint != 0x24)
    {
        fprintf(stderr, "Error: Dollar binary 0x24 decoded to U+%lX\n", codePoint);
        success = false;
    }

    binary = 0xC2A3; // Pound
    codePoint = utf8Decode(binary);
    if(codePoint != 0xA3)
    {
        fprintf(stderr, "Error: Pound binary 0xC2A3 decoded to U+%lX\n", codePoint);
        success = false;
    }

    binary = 0xE282ACu; // Euro
    codePoint = utf8Decode(binary);
    if(codePoint != 0x20AC)
    {
        fprintf(stderr, "Error: Euro binary 0xE282AC decoded to U+%lX\n", codePoint);
        success = false;
    }

    binary = 0xD098; // Cyrillic I
    codePoint = utf8Decode(binary);
    if(codePoint != 0x0418)
    {
        fprintf(stderr, "Error: Cyrillic I binary 0xD098 decoded to U+%lX\n", codePoint);
        success = false;
    }

    binary = 0xF0908D88u; // Hwair
    codePoint = utf8Decode(binary);
    if(codePoint != 0x10348u)
    {
        fprintf(stderr, "Error: Hwair binary 0xF0908D88 decoded to U+%lX\n", codePoint);
        success = false;
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

