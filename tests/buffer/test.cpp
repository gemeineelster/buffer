#include "CppUTest/TestHarness.h"


/*extern "C" {
    #include "buffer.h"
}*/
#include "buffer.h"


TEST_GROUP(buffer_test_group) {

};

TEST(buffer_test_group, bufferCreate_param4_checkSize) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 4);

    CHECK_EQUAL(buffer_handle->size, 4);

    bufferDestroy(buffer_handle);
    //CHECK_EQUAL(buffer_handle, NULL);
}

TEST(buffer_test_group, bufferCreate_param5_checkSize) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 4);

    CHECK_EQUAL(buffer_handle->size, 4);

    bufferDestroy(buffer_handle);
}

TEST(buffer_test_group, bufferWrite_param_valid) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 6);

    int8_t rtn = bufferWrite(buffer_handle, (uint8_t*) "Test\n");

    CHECK_EQUAL(rtn, 0);
    CHECK_EQUAL(buffer_handle->writeIndex, 4);
    CHECK_EQUAL(buffer_handle->empty, false);
    CHECK_EQUAL(buffer_handle->full, false);
    CHECK_EQUAL(buffer_handle->overflow, false);

    bufferDestroy(buffer_handle);
}

TEST(buffer_test_group, bufferWrite_param_maxLength) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 4);

    int8_t rtn = bufferWrite(buffer_handle, (uint8_t*) "Test\n");

    CHECK_EQUAL(rtn, 0);
    CHECK_EQUAL(buffer_handle->writeIndex, 0);
    CHECK_EQUAL(buffer_handle->empty, false);
    CHECK_EQUAL(buffer_handle->full, true);
    CHECK_EQUAL(buffer_handle->overflow, true);

    bufferDestroy(buffer_handle);
}

TEST(buffer_test_group, bufferRead_bufferFull) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 4);

    int8_t rtn = bufferWrite(buffer_handle, (uint8_t*) "Test\n");

    CHECK_EQUAL(rtn, 0);
    CHECK_EQUAL(buffer_handle->full, true);
    CHECK_EQUAL(buffer_handle->overflow, true);
    uint8_t read = bufferRead(buffer_handle);

    CHECK_EQUAL(read, 'T');
    //CHECK_EQUAL(buffer_handle->full, false);
    bufferDestroy(buffer_handle);
}