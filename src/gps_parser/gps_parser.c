#include "gps_parser.h"


ENUM_NMEA_TYPE_t getNMEA_type(char *data) {
    int i = 0;
    char str_type[8] = {0};
    
    if (data[0] != '$') {
        return NONE;
    }
    else {
        i = 1;
    }
    while(data[i] != '\0' && data[i] != ',') {
        str_type[i-1] = data[i];
        i++;
    }

    if (!strcmp(str_type, "GNGGA")) {
        return GNGGA;
    } else if (!strcmp(str_type, "GNVTG")) {
        return GNVTG;
    } else if (!strcmp(str_type, "GNGSA")) {
        return GNGGA;
    } else if (!strcmp(str_type, "GPGSV")) {
        return GPGSV;
    } else if (!strcmp(str_type, "GNRMC")) {
        return GNRMC;
    } else if (!strcmp(str_type, "GNZDA")) {
        return GNZDA;
    } else if (!strcmp(str_type, "PASHR")) {
        return PASHR;
    } else {
        return NONE;
    }
}

void resetGNGGA(GNGGA_t *data) {
    if (data == NULL) {
        return;
    }

    data->utc = 0.0;
    data->latitude = 0.0;
    data->hemisphere_north = false;
    data->longitude = 0.0;
    data->hemisphere_east = false;
    data->gps_quality = NO_QUALITY_VALUE;
    data->used_satalites = 0;
    data->hdop = 0.0;
    data->altitude_geoid_height = 0.0;
    data->unit_of_altitude = 'X';
    data->geoidal_seperation = 0.0;
    data->unit_of_geoidal_seperation = 'X';
    data->age_of_differential_data[0] = '\0';
    data->differential_reference_station_ID[0] = '\0';    
}

int parseGNGGA(char *data, GNGGA_t *gngga_data) {
    if (data == NULL || gngga_data == NULL) {
        return -1;
    }

    resetGNGGA(gngga_data);

    char segment[16] = "";
    uint8_t cnt_segment = 0;
    uint8_t i = 0;
    uint8_t no_of_seperator = 0;

    while (data[i] != '\0' && i < 254) {
        if (data[i] == ',' || data[i] == '\r') {
            switch(no_of_seperator) {
                case 0:
                    if (strcmp("$GNGGA", segment)) {
                        return -1;
                    }
                    break;

                case 1:
                    //UTC
                    gngga_data->utc = atof(segment);
                    break;

                case 2:
                    //Latitude
                    gngga_data->latitude = atof(segment);
                    break;
                
                case 3:
                    //Hemisphere_north
                    if (segment[0] == 'N') {
                        gngga_data->hemisphere_north = true;
                    } else {
                        gngga_data->hemisphere_north = false;
                    }
                    break;

                case 4:
                    //Longitude
                    gngga_data->longitude = atof(segment);
                    break;

                case 5:
                    //Hemisphere_east
                    if (segment[0] == 'E') {
                        gngga_data->hemisphere_east = true;
                    } else {
                        gngga_data->hemisphere_east = false;
                    }
                    break;

                case 6:
                    //GPS_quality
                    switch(atoi(segment)) {
                        case 0:
                            gngga_data->gps_quality = GNSS_NOT_AVAILABLE;
                            break;

                        case 1:
                            gngga_data->gps_quality = GNSS_VALID;
                            break;

                        case 4:
                            gngga_data->gps_quality = RTK_FIXED;
                            break;

                        case 5:
                            gngga_data->gps_quality = RTK_FLOAT;
                            break;

                        default:
                            gngga_data->gps_quality = NO_QUALITY_VALUE;
                            break;

                    }
                    break;

                case 7:
                    //Used_satalites
                    gngga_data->used_satalites = atoi(segment);
                    break;

                case 8:
                    //HDOP
                    gngga_data->hdop = atof(segment);
                    break;

                case 9:
                    //Altitude_geoid_height
                    gngga_data->altitude_geoid_height = atof(segment);
                    break;

                case 10:
                    //Unit_of_altitude
                    gngga_data->unit_of_altitude = segment[0];
                    break;

                case 11:
                    //Geoidal_seperation
                    gngga_data->geoidal_seperation = atof(segment);
                    break;

                case 12:
                    //Unit_of_geoidal_seperation
                    gngga_data->unit_of_geoidal_seperation = segment[0];
                    break;

                case 13:
                    //Age_of_differential_data
                    strcpy(gngga_data->age_of_differential_data, segment);
                    break;

                case 14:
                    //Differential_reference_station_ID
                    strcpy(gngga_data->differential_reference_station_ID, segment);
                    break;

                default:
                    return -1;

            }
            segment[0] = '\0';
            cnt_segment = 0;
            no_of_seperator++;
        }
        if (data[i] != ',') {
            segment[cnt_segment++] = data[i];
            segment[cnt_segment] = '\0';
        }
        
        i++;
    }

    return 0;
}