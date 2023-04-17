#include "buffer.h"



Buffer_Handler_t *bufferCreate(uint8_t size) {
	Buffer_Handler_t *buf = (Buffer_Handler_t*) malloc(sizeof(Buffer_Handler_t));
	buf->size = size;
	buf->data = (uint8_t*) calloc(size, sizeof(uint8_t));
 	buf->readIndex = 0;
	buf->writeIndex = 0;
	buf->overFlow = false;
	buf->full = false;

	return buf;
}

int8_t bufferDestroy(Buffer_Handler_t *buf) {
	// Destroying an reallocating buffer
	if (buf == NULL) {
		return -1;
	}

	buf->size = 0;
	free(buf->data);
	buf->readIndex = 0;
	buf->writeIndex = 0;
	buf->overFlow = false;
	buf->full = false;

	free(buf);
	return -1;
}

int8_t bufferWrite(Buffer_Handler_t *buf, uint8_t *data) {
	uint8_t cnt_data = 0;

	if(buf == NULL) {
		return -1;
	}

	while (data[cnt_data] != '\n') {
		buf->data[buf->writeIndex++] = data[cnt_data++];

		if (buf->writeIndex >= buf->size) {
			buf->writeIndex = 0;
			buf->overFlow = true;
		}
	}

	return 0;
}

uint8_t bufferRead(Buffer_Handler_t* buf) {
	/*if (buf == NULL) {
		return NULL;
	}
	if (buf->writeIndex == buf->readIndex) {
		return NULL;
	}*/

	return buf->data[buf->readIndex++];
}
