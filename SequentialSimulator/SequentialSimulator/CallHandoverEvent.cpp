#include "CallHandoverEvent.h"

CallHandoverEvent::CallHandoverEvent(float t, float s, int bid, float d)
	:Event(t, bid)
{
	speed = s;
	duration = d;
}

void CallHandoverEvent::handleEvent(Base blist[]){
	Base *base = &blist[baseID];
	Base *prevBase = &blist[baseID-1];
	prevBase->decOccupiedChannel();
	//cout<<base->toString();
	int oc = base->getOccupiedChannel();
	if(oc<10){//not all the channel occupied
		base->incOccupiedChannel();
		float handoverTS = time+3600*DIAMETER/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS && baseID+1<19)
			new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS);
		else
			new CallTerminationEvent(terminationTS, baseID);
	}else //all the channel occupied
		Event::drop++;
}

string CallHandoverEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t"<<"Hando\t\t"<<time
		<<"\t"<<baseID<<"\t"<<speed<<"\t"<<duration<<std::endl;
	return ss.str();
}
