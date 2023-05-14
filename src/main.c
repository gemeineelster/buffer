
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

    ArrayBuffer_Handler_t *arrBuff = arrayBufferCreate(8, 16);

    arrayBufferDestroy(arrBuff);


    printf("Hello World");
    
    return 0;
}