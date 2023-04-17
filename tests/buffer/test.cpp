#include "CppUTest/TestHarness.h"


extern "C" {
    #include "buffer.h"
}

TEST_GROUP(buffer_test_group) {
    void setup() {
        //Buffer_Handler_t *buf_handle = bufferCreate((uint8_t) 16);
    }

    void teardown() {
        //bufferDestroy(buf_handle);
    }
};

TEST(buffer_test_group, bufferCreate_param4_checkSize) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 4);

    CHECK_EQUAL(buffer_handle->size, 4);

    bufferDestroy(buffer_handle);

    //CHECK_EQUAL(avg, 1.0);
    //POINTERS_EQUAL(buf_handle, NULL);
}
