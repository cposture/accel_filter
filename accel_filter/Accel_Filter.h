#ifndef ACCEL_FILTER_H
#define ACCEL_FILTER_H

#define SIGMA_FILTER_OPEN 1
typedef signed int int32;
typedef signed short int int16;

/* »úÐµÂË²¨ */
void movement_end_check(long int accel_n[3], long int vel[2][3]);
void position(long int accel_n[2][3], long int vel[2][3], long int displayment[2][3]);
#endif