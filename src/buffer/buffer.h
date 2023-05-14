/*
 * Buffer.h
 *
 *  Created on: 31.03.2023
 *      Author: nullachtfuenfzehn
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	uint8_t size;
	uint8_t readIndex;
	uint8_t writeIndex;
	uint8_t *data;
	bool overflow;
	bool full;
	bool empty;

} Buffer_Handler_t;

typedef enum {
	WARNING = -2,
	FAIL = -1,
	OK = 0,
}ENUM_RET;

Buffer_Handler_t *bufferCreate(uint8_t);
int8_t bufferDestroy(Buffer_Handler_t*);
ENUM_RET bufferWrite(Buffer_Handler_t*, uint8_t*, uint16_t size);
ENUM_RET bufferRead(Buffer_Handler_t*, uint8_t*, uint16_t *size);


#ifdef __cplusplus
}
#endif

#endif /* BUFFER_H_ */
