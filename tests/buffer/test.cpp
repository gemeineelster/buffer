#include "CppUTest/TestHarness.h"


/*extern "C" {
    #include "buffer.h"
}*/
#include "buffer.h"
#include <string.h>


TEST_GROUP(buffer_test_group) {
    Buffer_Handler_t *ptr_buf_4 = NULL;
    Buffer_Handler_t *ptr_buf_8 = NULL;
    char text_4[4] = {0};
    char text_8[8];
    char text_4_cr[5];
    char text_8_cr[9];

    char returnedData_4[5];

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

    CHECK_EQUAL(rtn, OK);
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

    CHECK_EQUAL(rtn, OK);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 0);
    CHECK_EQUAL(ptr_buf_4->readIndex, 0);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_TRUE(ptr_buf_4->full);
    CHECK_TRUE(ptr_buf_4->overflow);
}

IGNORE_TEST(buffer_test_group, bufferWrite_paramData_toLong) {
    char data[9] = "TestFast";
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) data, 8);

    CHECK_EQUAL(rtn, WARNING);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 0);
    CHECK_EQUAL(ptr_buf_4->readIndex, 0);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_TRUE(ptr_buf_4->full);

    //int streq = strcmp((char*) data, "Fast");
    //CHECK_EQUAL(streq, 0);
    STRCMP_EQUAL("Fast", (char*) data);
}

TEST(buffer_test_group, bufferWrite_paramSize_writingWithOverflow) {
    uint16_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    CHECK_EQUAL(rtn, OK);
    STRCMP_EQUAL("Te", (char*) ptr_buf_4->data);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 2);
    CHECK_EQUAL(ptr_buf_4->readIndex, 2);
    CHECK_TRUE(ptr_buf_4->empty);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);

    CHECK_EQUAL(rtn, OK);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_EQUAL(ptr_buf_4->writeIndex, 1);
    CHECK_EQUAL(ptr_buf_4->overflow, true);
    CHECK_EQUAL(ptr_buf_4->full, false);
}

TEST(buffer_test_group, bufferRead_paramBuffer_isNull) {
    uint16_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);
    rtn = bufferRead(NULL, (uint8_t*) returnedData_4, &size);

    CHECK_EQUAL(rtn, FAIL);
}


TEST(buffer_test_group, bufferRead_paramBuffer_exactLength) {
    uint16_t size = 6;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Test", 4);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    int streq = strcmp((char*) ptr_buf_4->data, "Test");

    CHECK_EQUAL(rtn, OK);
    STRCMP_EQUAL("Test", (char*) returnedData_4);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(0, ptr_buf_4->readIndex);
}

TEST(buffer_test_group, bufferRead_paramSize_smallerThanExpected) {
    uint16_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    int streq = strcmp((char*) ptr_buf_4->data, "Tes");

    CHECK_EQUAL(rtn, OK);
    CHECK_EQUAL(streq, 0);
    CHECK_EQUAL(ptr_buf_4->readIndex, 3);
    CHECK_EQUAL(ptr_buf_4->overflow, false);
}

TEST(buffer_test_group, bufferRead_paramSize_writingWithOverflow_notFull) {
    uint16_t size = 4;

    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);
    CHECK_EQUAL(2, ptr_buf_4->writeIndex);
    CHECK_EQUAL(0, ptr_buf_4->readIndex);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->full);
    CHECK_FALSE(ptr_buf_4->overflow);

    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    CHECK_EQUAL(2, ptr_buf_4->writeIndex);
    CHECK_EQUAL(2, ptr_buf_4->readIndex);
    CHECK_TRUE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->full);
    CHECK_FALSE(ptr_buf_4->overflow);
    STRCMP_EQUAL("Te", (char*) returnedData_4);

    CHECK_EQUAL(rtn, OK);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Tes", 3);

    CHECK_EQUAL(1, ptr_buf_4->writeIndex);
    CHECK_EQUAL(2, ptr_buf_4->readIndex);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->full);
    CHECK_TRUE(ptr_buf_4->overflow);

    size = 5;

    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    CHECK_EQUAL(1, ptr_buf_4->writeIndex);
    CHECK_EQUAL(1, ptr_buf_4->readIndex);
    CHECK_EQUAL(rtn, OK);
    CHECK_EQUAL(size, 3);
    CHECK_TRUE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->overflow);
    CHECK_FALSE(ptr_buf_4->full);
}

TEST(buffer_test_group, bufferRead_paramSize_writingWithOverflow_isFull) {
    uint16_t size = 4;
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);

    CHECK_EQUAL(rtn, OK);

    size = 8;
    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Fast", 4);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    CHECK_EQUAL(rtn, OK);
    CHECK_EQUAL(size, 4);
    STRCMP_EQUAL("TeFa", (char*) returnedData_4);
    CHECK_TRUE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->overflow);
    CHECK_FALSE(ptr_buf_4->full);
}

TEST(buffer_test_group, bufferRead_testWithManyData) {
    uint16_t size = 5;
    uint8_t readData[8];
    ENUM_RET rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Te", 2);
    rtn = bufferRead(ptr_buf_4, (uint8_t*) returnedData_4, &size);

    CHECK_EQUAL(rtn, OK);
    STRCMP_EQUAL("Te", (char*) returnedData_4);
    CHECK_EQUAL(2, ptr_buf_4->writeIndex);
    CHECK_EQUAL(2, ptr_buf_4->readIndex);
    CHECK_FALSE(ptr_buf_4->overflow);
    CHECK_FALSE(ptr_buf_4->full);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Fas", 3);

    CHECK_EQUAL(1, ptr_buf_4->writeIndex);
    CHECK_EQUAL(2, ptr_buf_4->readIndex);
    CHECK_TRUE(ptr_buf_4->overflow);
    CHECK_FALSE(ptr_buf_4->full);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "t", 1);

    CHECK_EQUAL(2, ptr_buf_4->writeIndex);
    CHECK_EQUAL(2, ptr_buf_4->readIndex);
    CHECK_TRUE(ptr_buf_4->overflow);
    CHECK_TRUE(ptr_buf_4->full);

    CHECK_EQUAL(OK, rtn);

    size = 2;
    rtn = bufferRead(ptr_buf_4, readData, &size);
    CHECK_EQUAL(1, size);
    
    CHECK_EQUAL(2, ptr_buf_4->writeIndex);
    CHECK_EQUAL(3, ptr_buf_4->readIndex);
    CHECK_TRUE(ptr_buf_4->overflow);
    CHECK_FALSE(ptr_buf_4->full);
    STRCMP_EQUAL("F", (char*) readData);

    size = 4;
    rtn = bufferRead(ptr_buf_4, readData, &size);
    CHECK_EQUAL(OK, rtn);
    CHECK_EQUAL(2, ptr_buf_4->writeIndex);
    CHECK_EQUAL(2, ptr_buf_4->readIndex);
    CHECK_EQUAL(3, size);
    CHECK_FALSE(ptr_buf_4->full);
    CHECK_FALSE(ptr_buf_4->overflow);
    CHECK_TRUE(ptr_buf_4->empty);
    STRCMP_EQUAL("ast", (char*) readData);

    rtn = bufferWrite(ptr_buf_4, (uint8_t*) "Hallihallo", 10);
    CHECK_TRUE(ptr_buf_4->full);
    CHECK_FALSE(ptr_buf_4->empty);
    CHECK_TRUE(ptr_buf_4->overflow);

    size = 6;
    rtn = bufferRead(ptr_buf_4, (uint8_t*) readData, &size);
    CHECK_TRUE(ptr_buf_4->empty);
    CHECK_FALSE(ptr_buf_4->full);
    CHECK_FALSE(ptr_buf_4->overflow);
    STRCMP_EQUAL("Hall", (char*) readData);
    
}

TEST(buffer_test_group, bufferRead_paramSize_testWithManyData_2) {
    Buffer_Handler_t *buf = bufferCreate(16);

    char string1[] = "String1";
    char string2[] = "STRING2";
    char string3[] = "StRiNg3";
    char expData1[] = "String1STRING2St";
    char expData2[] = "STRING2StRiNg3St";
    uint16_t s = 20;
    char realData[20] = "";

    ENUM_RET ret;
    
    ret = bufferWrite(buf, (uint8_t*) string1, sizeof(string1));
    CHECK_EQUAL(OK, ret);
    ret = bufferWrite(buf, (uint8_t*) string2, sizeof(string2));
    CHECK_EQUAL(OK, ret);
    ret = bufferWrite(buf, (uint8_t*) string3, sizeof(string3));
    CHECK_EQUAL(WARNING, ret);

    ret = bufferRead(buf, (uint8_t*) realData, &s);
    STRCMP_EQUAL(expData1, realData);

    ret = bufferWrite(buf, (uint8_t*) string2, sizeof(string2));
    CHECK_EQUAL(OK, ret);
    ret = bufferWrite(buf, (uint8_t*) string3, sizeof(string3));
    CHECK_EQUAL(OK, ret);
    ret = bufferWrite(buf, (uint8_t*) string1, sizeof(string1));
    CHECK_EQUAL(WARNING, ret);

    s = 20;
    ret = bufferRead(buf, (uint8_t*) realData, &s);
    STRCMP_EQUAL(expData2, realData);

    bufferDestroy(buf);
}

