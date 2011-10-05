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
	Base *base = &blist[baseID];
	int oc = base->getOccupiedChannel(); //occupied channel 
	base->print();
	if(oc<10){
		base->incOccupiedChannel();
		float handoverTS = time + 3600*(DIAMETER-position)/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS)
			if(baseID+1<19)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS);
			else
				Event::success++;
		else
			new CallTerminationEvent(terminationTS, baseID);
	}else
		Event::block++;

}


string CallInitiationEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t"<<"Init\t\t"<<arrivalNo<<"\t\t"<<time<<"\t\t"
		<<baseID<<"\t\t"<<speed<<"\t\t"<<duration<<"\t\t"<<position<<std::endl;
	return ss.str();
}