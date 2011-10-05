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
	base->print();
	int oc = base->getOccupiedChannel();
	if(oc<10){//not all the channel occupied
		base->incOccupiedChannel();
		float handoverTS = time+3600*DIAMETER/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS)
			if(baseID+1)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS);
			else
				Event::success++;
		else
			new CallTerminationEvent(terminationTS, baseID);
	}else //all the channel occupied
		Event::drop++;
}

string CallHandoverEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t\t"<<"Hando\t\t\t\t"<<time
		<<"\t\t"<<baseID<<"\t\t"<<speed<<"\t\t"<<duration<<std::endl;
	return ss.str();
}
