#include "CppUTest/TestHarness.h"


/*extern "C" {
    #include "buffer.h"
}*/
#include "buffer.h"
#include <string.h>


TEST_GROUP(buffer_test_group) {
    Buffer_Handler_t *ptr_buf_4 = NULL;
    Buffer_Handler_t *ptr_buf_8 = NULL;
    char text_4[4];
    char text_8[8];
    char text_4_cr[5];
    char text_8_cr[9];

    char returnedData_4[4];

   void setup()
   {
        ptr_buf_4 = bufferCreate((uint8_t) 4);
        ptr_buf_8 = bufferCreate((uint8_t) 8);
        strcpy(text_4, "Vier");
        strcpy(text_8, "vierVier");
        strcpy(text_4_cr, "Vier\n");
        strcpy(text_8_cr, "vierVier\n");
        
        //printf("In text_4 steht %s", text_4);
   }

   void teardown()
   {
        bufferDestroy(ptr_buf_4);
        bufferDestroy(ptr_buf_8);
   }
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

TEST(buffer_test_group, buffer_after_init) {
    Buffer_Handler_t *buffer_handle = bufferCreate((uint8_t) 4);

    CHECK_TRUE(buffer_handle->empty);
    CHECK_FALSE(buffer_handle->full);
    CHECK_FALSE(buffer_handle->overflow);

    bufferDestroy(buffer_handle);
}

TEST(buffer_test_group, bufferWrite_paramBuf_isNull) {
    ENUM_RET ret = bufferWrite(NULL, (uint8_t*) NULL, 0);

    CHECK_EQUAL(ret, FAIL);
}

TEST(buffer_test_group, bufferWrite_param_NULL) {
    ENUM_RET ret = bufferWrite(ptr_buf_4, (uint8_t*) NULL, 0);

    CHECK_EQUAL(ret, FAIL);
}

TEST(buffer_test_group, bufferWrite_paramData_valid) {
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);

    int streq = strcmp((char*) ptr_buf_4->data, "Tes");

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 3);
    CHECK_EQUAL(ptr_buf_4->readIndex, 0);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->full);
    CHECK_FALSE(ptr_buf_4->overflow);
}

TEST(buffer_test_group, bufferWrite_paramData_exactSize) {
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Test", 4);

    int streq = strcmp((char*) ptr_buf_4->data, "Test");

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 0);
    CHECK_EQUAL(ptr_buf_4->readIndex, 0);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_TRUE(ptr_buf_4->full);
    CHECK_TRUE(ptr_buf_4->overflow);
}

IGNORE_TEST(buffer_test_group, bufferWrite_paramData_toLong) {
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "TestFast", 8);

    CHECK_EQUAL(rtn, WARNING);
    //CHECK_EQUAL(ptr_buf_4->writeIndex, 0);
    //CHECK_EQUAL(ptr_buf_4->readIndex, 0);
    //CHECK_FALSE(ptr_buf_4->empty);
    //CHECK_TRUE(ptr_buf_4->full);
    //CHECK_TRUE(ptr_buf_4->overflow);
}

TEST(buffer_test_group, bufferWrite_paramSize_writingWithOverflow) {
    uint8_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    int streq = strcmp((char*) ptr_buf_4->data, "Te");

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 2);
    CHECK_EQUAL(ptr_buf_4->readIndex, 2);
    CHECK_TRUE(ptr_buf_4->empty);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 1);
    CHECK_EQUAL(ptr_buf_4->overflow, true);
    CHECK_EQUAL(ptr_buf_4->full, false);
}

TEST(buffer_test_group, bufferRead_paramBuffer_isNull) {
    uint8_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);
    rtn = bufferRead(NULL, (uint8_t*) returnedData_4, size);

    //int streq = strcmp((char*) ptr_buf_4->data, "Tes");

    CHECK_EQUAL(rtn, FAIL);
}


TEST(buffer_test_group, bufferRead_paramBuffer_exactLength) {
    uint8_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Test", 4);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    int streq = strcmp((char*) ptr_buf_4->data, "Test");

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->readIndex, 4);
}

TEST(buffer_test_group, bufferRead_paramSize_smallerThanExpected) {
    uint8_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    int streq = strcmp((char*) ptr_buf_4->data, "Tes");

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->readIndex, 3);
    CHECK_EQUAL(ptr_buf_4->overflow, false);
}

TEST(buffer_test_group, bufferRead_paramSize_writingWithOverflow_notFull) {
    uint8_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    CHECK_EQUAL(rtn, SUCCESS);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(size, 4);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 1);
    CHECK_EQUAL(ptr_buf_4->overflow, true);
    CHECK_FALSE(ptr_buf_4->full);
}

TEST(buffer_test_group, bufferRead_paramSize_writingWithOverflow_isFull) {
    uint8_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    CHECK_EQUAL(rtn, SUCCESS);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Test", 4);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, size);

    CHECK_EQUAL(rtn, SUCCESS);
    CHECK_EQUAL(size, 4);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 2);
    CHECK_EQUAL(ptr_buf_4->overflow, true);
    CHECK_TRUE(ptr_buf_4->full);
}
