#ifndef BEACON_H
#define BEACON_H

#include <AM.h>

enum{
	AM_BEACON=0xC8,
	TIMER_PERIOD_MILLI=8000	
};

typedef nx_struct BeaconMsg{
	nx_uint8_t student_No[3];
}BeaconMsg;

typedef nx_struct BaseStationMsg{
	nx_uint8_t student_No[3];
	nx_uint8_t sensor_No[2];
}BaseStationMsg;

#endif
