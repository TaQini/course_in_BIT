// Sensor 1
// recvie 2 msg 
// send msg+sensor_id to 0
#include "Timer.h"
#include "Beacon.h"
#include "printf.h"

module BeaconC{
	uses interface Boot;
	uses interface Timer<TMilli> as Timer0;	
	uses interface SplitControl as AMControl;
	uses interface Packet as AMPacket;
	uses interface AMSend;
	uses interface Receive as AMReceive;
}

implementation{
	message_t pkt;
	bool SendBusy=FALSE;

	nx_uint8_t student0;
	nx_uint8_t student1;
	nx_uint8_t student2;
	nx_uint8_t sensor0;
	nx_uint8_t sensor1;
	
	event void Boot.booted(){
		call AMControl.start();
	}
	
	event void AMControl.startDone(error_t err){
		if(err!=SUCCESS){
			call AMControl.start();
		}
		else{
			call Timer0.startPeriodic(TIMER_PERIOD_MILLI);
		}
	}
	
	event void AMControl.stopDone(error_t err){}	
	
	event void Timer0.fired(){
		
		BaseStationMsg* SendMsg=(BaseStationMsg*)call AMSend.getPayload(&pkt,sizeof(BaseStationMsg));
		SendMsg->student_No[0]= student0 ;
		SendMsg->student_No[1]= student1 ;
		SendMsg->student_No[2]= student2 ;
		SendMsg->sensor_No[0] = sensor0;
		SendMsg->sensor_No[1] = sensor1; // pgk to send to sensor 0

		if(call AMSend.send(0,&pkt,sizeof(BaseStationMsg))!=SUCCESS){
			SendBusy=FALSE; // sned to sensor 0
		}
		else{
			SendBusy=TRUE;
		}
	}

	event void AMSend.sendDone(message_t* msg,error_t err){
		if(&pkt==msg){
			SendBusy=FALSE;
		}
	}

	event message_t* AMReceive.receive(message_t* msg, void* payload, uint8_t len){
	if (len == sizeof(BeaconMsg)) {
    	BeaconMsg* btrpkt = (BeaconMsg*)payload;
    	student0 = btrpkt->student_No[0];
    	student1 = btrpkt->student_No[1];
    	student2 = btrpkt->student_No[2];
    	sensor0 = 2;
    	sensor1 = TOS_NODE_ID;
    }

    return msg;
  }
}
