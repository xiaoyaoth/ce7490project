#include "CallHandoverEvent.h"

CallHandoverEvent::CallHandoverEvent(float t, float s, int bid, float d)
	:Event(t, bid)
{
	speed = s;
	duration = d;
}

void CallHandoverEvent::handleEvent(Base blist[]){
	Base base = blist[baseID];
	Base prevBase = blist[baseID-1];
	prevBase.decOccupiedChannel();
	int oc = base.getOccupiedChannel();
	if(oc<=9){//not all the channel occupied
		Event::handover++;
		base.incOccupiedChannel();
		float handoverTS = time+3600*DIAMETER/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS)
			new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS);
		else
			new CallTerminationEvent(terminationTS, baseID);
	}else //all the channel occupied
		Event::drop++;
}

string CallHandoverEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t"<<"Handover\t\t"<<time
		<<"\t"<<baseID<<"\t"<<duration<<"\t"<<speed<<std::endl;
	return ss.str();
}
