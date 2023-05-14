
#include <stdio.h>
//#include "average.h"
#include "buffer/buffer.h"


int main()
{
    /*float array[] = {-1.0, 0.0, 1.0, 2.0, 3.0};
    float avg = average(array, 5);
    printf("Average: %f\r\n", avg);*/
    char string1[] = "String1";
    char string2[] = "STRING2";
    char string3[] = "StRiNg3";
    uint8_t rString[20] = "";
    uint16_t s = 20;

    Buffer_Handler_t *buf_handle = bufferCreate(16);

    bufferWrite(buf_handle, (uint8_t*) string1, sizeof(string1));
    bufferWrite(buf_handle, (uint8_t*) string2, sizeof(string2));
    bufferWrite(buf_handle, (uint8_t*) string3, sizeof(string3));

    bufferRead(buf_handle, rString, &s);

    bufferDestroy(buf_handle);

    printf("Hello World");
    
    return 0;
}