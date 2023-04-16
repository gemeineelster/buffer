#include "Buffer.h"



Buffer_Handler_t *bufferCreate(uint8_t size) {
	Buffer_Handler_t *buffer = (Buffer_Handler_t*) malloc(sizeof(Buffer_Handler_t));
	buffer->size = size;
	buffer->data = (uint8_t*) calloc(size, sizeof(uint8_t));
 	buffer->readIndex = 0;
	buffer->writeIndex = 0;
	buffer->overFlow = false;
	buffer->full = false;

	return buffer;
}

int8_t bufferDestroy(Buffer_Handler_t *buffer) {
	// Destroying an reallocating buffer
	return -1;
}

int8_t bufferWrite(Buffer_Handler_t *buffer, uint8_t *data) {
	uint8_t cnt_data = 0;

	if(buffer == NULL) {
		return -1;
	}

	while (data[cnt_data] != '\n') {
		buffer->data[buffer->writeIndex++] = data[cnt_data++];

		if (buffer->writeIndex >= buffer->size) {
			buffer->writeIndex = 0;
			buffer->overFlow = true;
		}
	}

	return 0;
}

uint8_t bufferRead(Buffer_Handler_t* buffer) {
	if (buffer == NULL) {
		return NULL;
	}
	if (buffer->writeIndex == buffer->readIndex) {
		return NULL;
	}

	return buffer->data[buffer->readIndex++];
}
