#include "CppUTest/TestHarness.h"


/*extern "C" {
    #include "buffer.h"
}*/
#include "gps_parser.h"
#include <string.h>


TEST_GROUP(gps_parser_test) {
    /*char *string_gprmc = "$GPRMC,130303.0,A,4717.115,N,00833.912,E,000.03,043.4,200601,01.3,W*7D\r\n";
    char *string_gpzda = "GPZDA,130304.2,20,06,2001,,*56\r\n";
    char *string_gpgga = "$GPGGA,130304.0,4717.115,N,00833.912,E,1,08,0.94,00499,M,047,M,,*59\r\n";
    char *string_gpgll = "$GPGLL,4717.115,N,00833.912,E,130304.0,A*33\r\n";
    char *string_gpvtg = "$GPVTG,205.5,T,206.8,M,000.04,N,000.08,K*4C\r\n";
    char *string_gpgsa = "$GPGSA,A,3,13,20,11,29,01,25,07,04,,,,,1.63,0.94,1.33*04\r\n";
    char *string_gpgsv_1 = "$GPGSV,2,1,8,13,15,208,36,20,80,358,39,11,52,139,43,29,13,044,36*42\r\n";
    char *string_gpgsv_2 = "$GPGSV,2,2,8,01,52,187,43,25,25,074,39,07,37,286,40,04,09,306,33*44\r\n";*/

    char string_gngga[128];
    char string_gnvtg[128];
    char string_gngsa[128];
    char string_gpgsv[128];
    char string_gnrmc[128];
    char string_gnzda[128];
    char string_pashr[128];


   void setup()
   {
        strcpy(string_gngga, "$GNGGA,185833.80,4808.7402397,N,01133.9325039,E,5,15,1.1,470.50,M,45.65,M,,*75");
        strcpy(string_gnvtg, "$GNVTG,112.99,T,109.99,M,0.15,N,0.08,K,A*3B");
        strcpy(string_gngsa, "$GNGSA,2,M,06,12,15,17,19,24,25,32,1.34,0.96,0.93*1D");
        strcpy(string_gpgsv, "$GPGSV,6,1,10,02,3.6,133.2,26,10,06,11.7,100.7,39,10,10,9.6,281.5,35,10,12,63.1,256.5,46*58");
        strcpy(string_gnrmc, "$GNRMC,185823.40,A,4808.7402374,N,01133.9324760,E,0.00,112.64,130117,3.00,E,A*14");
        strcpy(string_gnzda, "$GNZDA,185823.40,13,01,2017,,*7E");
        strcpy(string_pashr, "$PASHR,190558.56,107.09,T,,-0.16,,,0.067,0.056,2*34");
   }

   void teardown()
   {

   }
};

TEST(gps_parser_test, getNMEA_tpye) {
    CHECK_EQUAL(GNGGA, getNMEA_type(string_gngga));
    CHECK_EQUAL(GNGGA, getNMEA_type(string_gngga));
}