#include "CppUTest/TestHarness.h"


/*extern "C" {
    #include "buffer.h"
}*/
#include "buffer.h"
#include <string.h>


TEST_GROUP(arrayBuffer_test_group) {
    ArrayBuffer_Handler_t *arrBuf = NULL;
    uint8_t retData[20] = "";
    uint16_t size_retData = 20;
    uint16_t size_arrBuf = 4;
    uint16_t size_arrBufEach = 16;

    char string1[16] = "";
    char string2[16] = "";
    char string3[16] = "";
    char string4[16] = "";
    char string5[16] = "";

   void setup()
   {
        arrBuf = arrayBufferCreate(size_arrBuf, size_arrBufEach);
        strcpy(string1, "String1");
        strcpy(string2, "STRING2");
        strcpy(string3, "StRiNg3");
        strcpy(string4, "sTrInG4");
        strcpy(string5, "string5");
        //strcpy((char*) retData, "\0");

   }

   void teardown()
   {
        arrayBufferDestroy(arrBuf);
   }
};

IGNORE_TEST(arrayBuffer_test_group, arrayBufferCreate_valid) {
    ArrayBuffer_Handler_t * arrBuff = arrayBufferCreate((uint16_t) 4, (uint16_t) 8);

    CHECK_TRUE(arrBuff->empty);
    CHECK_FALSE(arrBuff->full);
    CHECK_FALSE(arrBuff->overflow);

    ENUM_RET ret = arrayBufferDestroy(arrBuff);

    CHECK_EQUAL(OK, ret);
    POINTERS_EQUAL(NULL, arrBuff->arrData);
}

TEST(arrayBuffer_test_group, arrayBufferDestroy_paramIsNull) {
    ArrayBuffer_Handler_t * arrBuff = arrayBufferCreate((uint16_t) 4, (uint16_t) 8);

    ENUM_RET ret = arrayBufferDestroy(NULL);

    CHECK_EQUAL(FAIL, ret);

    ret = arrayBufferDestroy(arrBuff);
    CHECK_EQUAL(OK, ret);
}

IGNORE_TEST(arrayBuffer_test_group, arrayBufferWrite_oneString) {

    ENUM_RET ret = arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string1));

    CHECK_EQUAL(OK, ret);
}

IGNORE_TEST(arrayBuffer_test_group, arrayBufferRead_twoStrings) {
    ENUM_RET ret = arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string1));
    ret = arrayBufferWrite(arrBuf, (uint8_t*) string2, sizeof(string2));
    ret = arrayBufferRead(arrBuf, retData, size_retData);

    CHECK_EQUAL(OK, ret);
    STRCMP_EQUAL(string1, (char*) retData);

    ret = arrayBufferRead(arrBuf, retData, size_retData);

    CHECK_EQUAL(OK, ret);
    STRCMP_EQUAL(string2, (char*) retData);
}

TEST(arrayBuffer_test_group, arrayBufferRead_true) {
    ENUM_RET ret = arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string1));
    CHECK_EQUAL(OK, ret);

    ret = arrayBufferWrite(arrBuf, (uint8_t*) string2, sizeof(string2));
    CHECK_EQUAL(OK, ret);

    ret = arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string2));
    CHECK_EQUAL(OK, ret);

    ret = arrayBufferRead(arrBuf, retData, sizeof(retData));
    CHECK_EQUAL(OK, ret);
}

IGNORE_TEST(arrayBuffer_test_group, arrayBufferRead_writeToManyData_FAIL) {
    ENUM_RET ret = arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string1));
    ret = arrayBufferWrite(arrBuf, (uint8_t*) string2, sizeof(string2));
    //ret = arrayBufferWrite(arrBuf, (uint8_t*) string3, sizeof(string3));
    //ret = arrayBufferWrite(arrBuf, (uint8_t*) string4, sizeof(string4));
    //ret = arrayBufferWrite(arrBuf, (uint8_t*) string5, sizeof(string5));

    CHECK_EQUAL(OK, ret);
}

IGNORE_TEST(arrayBuffer_test_group, arrayBufferRead_true3) {
    CHECK_TRUE(true);
}

IGNORE_TEST(arrayBuffer_test_group, arrayBufferRead_true4) {
    CHECK_TRUE(true);
}
