
#include <stdio.h>
//#include "average.h"
#include "buffer/buffer.h"


int main()
{
    char string1[] = "String1";
    char string2[] = "STRING2";
    char string3[] = "StRiNgSTRING3";
    uint8_t rString[20] = "asdf";
    uint16_t s = 20;

    ArrayBuffer_Handler_t *arrBuf = arrayBufferCreate(4, 8);

    arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string1));
    arrayBufferWrite(arrBuf, (uint8_t*) string2, sizeof(string1));

    arrayBufferRead(arrBuf, rString, sizeof(rString));
    arrayBufferRead(arrBuf, rString, sizeof(rString));

    arrayBufferDestroy(arrBuf);


    printf("Hello World");
    
    return 0;
}