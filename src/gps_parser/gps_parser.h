#ifndef GPS_PARSER_H_
#define GPS_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NONE = -1,
    GNGGA = 0,
    GNVTG = 1,
    GNGSA = 2,
    GPGSV = 3,
    GNRMC = 4,
    GNZDA = 5,
    PASHR = 6,

} ENUM_NMEA_TYPE_t;

typedef enum {
    NO_QUALITY_VALUE = -1,
    GNSS_NOT_AVAILABLE = 0,
    GNSS_VALID = 1,
    RTK_FIXED = 4,
    RTK_FLOAT = 5
} ENUM_GPS_QUALITY_INDIKATOR;

typedef struct {
    float utc;
    float latitude;
    bool hemisphere_north;
    float longitude;
    bool hemisphere_east;
    ENUM_GPS_QUALITY_INDIKATOR gps_quality;
    uint8_t used_satalites;
    float hdop;
    float altitude_geoid_height;
    char unit_of_altitude;
    float geoidal_seperation;
    char unit_of_geoidal_seperation;
    char age_of_differential_data[4];
    char differential_reference_station_ID[4];
} GNGGA_t;


ENUM_NMEA_TYPE_t getNMEA_type(char *data);
int parseGNGGA(char *data, GNGGA_t *gngga_data);


#ifdef __cplusplus
}
#endif

#endif /* GPS_PARSER_H_ */