
#include <stdio.h>
#include "average.h"
#include "buffer.h"


int main()
{
    float array[] = {-1.0, 0.0, 1.0, 2.0, 3.0};
    float avg = average(array, 5);
    printf("Average: %f\r\n", avg);

    Buffer_Handler_t *buf_handle = bufferCreate(16);

    bufferWrite(buf_handle, (uint8_t*) "Hello");
    
    return 0;
}