
#include <stdio.h>
//#include "average.h"
#include "buffer/buffer.h"
#include "gps_parser/gps_parser.h"


int main()
{
    /*char string1[] = "String1";
    char string2[] = "STRING2";
    char string3[] = "StRiNgSTRING3";
    uint8_t rString[20] = "asdf";
    uint16_t s = 20;

    ArrayBuffer_Handler_t *arrBuf = arrayBufferCreate(4, 8);

    arrayBufferWrite(arrBuf, (uint8_t*) string1, sizeof(string1));
    arrayBufferWrite(arrBuf, (uint8_t*) string2, sizeof(string1));

    arrayBufferRead(arrBuf, rString, sizeof(rString));
    arrayBufferRead(arrBuf, rString, sizeof(rString));

    arrayBufferDestroy(arrBuf);


    printf("Hello World");*/

    char string_gngga[128];
    char string_gngga2[128];
    char string_gnvtg[128];
    char string_gngsa[128];
    char string_gpgsv[128];
    char string_gnrmc[128];
    char string_gnzda[128];
    char string_pashr[128];

    strcpy(string_gngga, "$GNGGA,185833.80,4808.7402397,N,01133.9325039,E,5,15,1.1,470.50,M,45.65,M,,*75\r");
    strcpy(string_gngga2, "$GNGGA,185833.80,,S,,W,5,3,1.1,470.50,M,45.65,M,,*75\r");
    strcpy(string_gnvtg, "$GNVTG,112.99,T,109.99,M,0.15,N,0.08,K,A*3B\r");
    strcpy(string_gngsa, "$GNGSA,2,M,06,12,15,17,19,24,25,32,1.34,0.96,0.93*1D\r");
    strcpy(string_gpgsv, "$GPGSV,6,1,10,02,3.6,133.2,26,10,06,11.7,100.7,39,10,10,9.6,281.5,35,10,12,63.1,256.5,46*58\r");
    strcpy(string_gnrmc, "$GNRMC,185823.40,A,4808.7402374,N,01133.9324760,E,0.00,112.64,130117,3.00,E,A*14\r");
    strcpy(string_gnzda, "$GNZDA,185823.40,13,01,2017,,*7E\r");
    strcpy(string_pashr, "$PASHR,190558.56,107.09,T,,-0.16,,,0.067,0.056,2*34\r");

    ENUM_NMEA_TYPE_t t = getNMEA_type(string_gngga);
    t = getNMEA_type(string_gnvtg);
    t = getNMEA_type(string_gngsa);
    t = getNMEA_type(string_gpgsv);
    t = getNMEA_type(string_gnrmc);
    t = getNMEA_type(string_gnzda);
    t = getNMEA_type(string_pashr);

    GNGGA_t d;
    d.latitude = 12.2;
    parseGNGGA(string_gngga, &d);
    parseGNGGA(string_gngga2, &d);
    
    return 0;
}