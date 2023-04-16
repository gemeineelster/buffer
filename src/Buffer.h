/*
 * Buffer.h
 *
 *  Created on: 31.03.2023
 *      Author: nullachtfuenfzehn
 */

#ifndef INC_UTIL_BUFFER_H_
#define INC_UTIL_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	uint8_t size;
	uint8_t readIndex;
	uint8_t writeIndex;
	uint8_t *data;
	bool overFlow;
	bool full;

} Buffer_Handler_t;

Buffer_Handler_t *bufferCreate(uint8_t);
int8_t bufferWrite(Buffer_Handler_t*, uint8_t*);


#ifdef __cplusplus
}
#endif

#endif /* INC_UTIL_BUFFER_H_ */
