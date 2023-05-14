#include "CppUTest/TestHarness.h"


/*extern "C" {
    #include "buffer.h"
}*/
#include "gps_parser.h"
#include <string.h>


TEST_GROUP(gps_parser_test) {
    char *string_gprmc = "$GPRMC,130303.0,A,4717.115,N,00833.912,E,000.03,043.4,200601,01.3,W*7D\r\n";
    char *string_gpzda = "GPZDA,130304.2,20,06,2001,,*56\r\n";
    char *string_gpgga = "$GPGGA,130304.0,4717.115,N,00833.912,E,1,08,0.94,00499,M,047,M,,*59\r\n";
    char *string_gpgll = "$GPGLL,4717.115,N,00833.912,E,130304.0,A*33\r\n";
    char *string_gpvtg = "$GPVTG,205.5,T,206.8,M,000.04,N,000.08,K*4C\r\n";
    char *string_gpgsa = "$GPGSA,A,3,13,20,11,29,01,25,07,04,,,,,1.63,0.94,1.33*04\r\n";
    char *string_gpgsv_1 = "$GPGSV,2,1,8,13,15,208,36,20,80,358,39,11,52,139,43,29,13,044,36*42\r\n";
    char *string_gpgsv_2 = "$GPGSV,2,2,8,01,52,187,43,25,25,074,39,07,37,286,40,04,09,306,33*44\r\n";

   void setup()
   {
        
        //printf("In text_4 steht %s", text_4);
   }

   void teardown()
   {

   }
};