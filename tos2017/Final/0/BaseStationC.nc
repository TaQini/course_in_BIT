#include "Timer.h"
#include "Beacon.h"
#include "printf.h"

module BaseStationC{
	uses interface Boot;
	
	uses interface SplitControl as AMControl;
	uses interface Packet as AMPacket;	
	uses interface Receive as AMReceive;
}

implementation{
	message_t pkt;

	event void Boot.booted(){
		call AMControl.start();
	}
	
	event void AMControl.startDone(error_t err){
		if(err!=SUCCESS){
			call AMControl.start();
		}
	}
	
	event void AMControl.stopDone(error_t err){}
	
	event message_t* AMReceive.receive(message_t* msg,void* p,uint8_t len){
		if(len==sizeof(BaseStationMsg)){
			BaseStationMsg* receiveMsg=(BaseStationMsg*)p;
			printf("///////////////////////////\n");
			printf("student_No: %d %d %d\n",receiveMsg->student_No[0],receiveMsg->student_No[1],receiveMsg->student_No[2]);
			printf("sensor_No: %d %d\n",receiveMsg->sensor_No[0],receiveMsg->sensor_No[1]);
			printf("///////////////////////////\n");
			printfflush();
		}
		return msg;
	}
	
}
