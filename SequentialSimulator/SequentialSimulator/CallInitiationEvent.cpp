#include "CallInitiationEvent.h"

CallInitiationEvent::CallInitiationEvent(float t, float s, int bid, float p, float d, int no)
	:Event(t, bid)
{
	arrivalNo = no;
	speed = s;
	position = p;
	duration = d;
}

void CallInitiationEvent::handleEvent(Base blist[]){
	Base base = blist[baseID];
	int oc = base.getOccupiedChannel(); //occupied channel 
	if(oc<=9){
		base.incOccupiedChannel();
		float handoverTS = time + 3600*(DIAMETER-RADIUS)/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS)
			new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS);
		else
			new CallTerminationEvent(terminationTS, baseID);
	}else
		Event::block++;

}


string CallInitiationEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t"<<"initiation\t"<<arrivalNo<<"\t"<<time<<"\t"
		<<baseID<<"\t"<<speed<<"\t"<<duration<<"\t"<<position<<std::endl;
	return ss.str();
}