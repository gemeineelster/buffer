#include "buffer.h"



Buffer_Handler_t *bufferCreate(uint8_t size) {
	Buffer_Handler_t *buf = (Buffer_Handler_t*) malloc(sizeof(Buffer_Handler_t));
	buf->size = size;
	buf->data = (uint8_t*) calloc(size + 1, sizeof(uint8_t));
 	buf->readIndex = 0;
	buf->writeIndex = 0;
	buf->overflow = false;
	buf->full = false;
	buf->empty = true;

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
	buf->overflow = false;
	buf->full = false;

	free(buf);
	return -1;
}

ENUM_RET bufferWrite(Buffer_Handler_t *buf, uint8_t *data, uint8_t size) {
	if(buf == NULL || data == NULL || size == 0) {
		return FAIL;
	}

	for (uint8_t i = 0; i < size; i++) {
		if (buf->full) {
			/*Test Begin*/
			//strcpy(data, "Fast");
			/*Test End*/
			return WARNING;
		}

		buf->data[buf->writeIndex++] = data[i];
		buf->empty = false;

		if (buf->writeIndex == buf->size) {
			buf->writeIndex = 0;
			buf->overflow = true;
		}

		if (buf->writeIndex == buf->readIndex && buf->overflow) {
			buf->full = true;
		}
	}

	return SUCCESS;
}

ENUM_RET bufferRead(Buffer_Handler_t* buf, uint8_t* data, uint8_t *size) {
	volatile uint8_t readSize = 0;
	if (buf == NULL) {
		return FAIL;
	}

	strcpy((char*) data, "\0");
	
	for (int i = 0; i < *size; i++) {
		data[i] = buf->data[buf->readIndex++];
		buf->full = false;
		readSize++;

		if (buf->readIndex >= buf->size) {
			buf->readIndex = 0;
			buf->overflow = false;
		}

		if (i >= *size) {
			break;
		}

		if (buf->readIndex == buf->writeIndex) {
			buf->empty = true;
			break;
		}
	}

	data[readSize] = '\0';

	*size = readSize;

	return SUCCESS;
}
