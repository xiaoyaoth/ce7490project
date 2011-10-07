#include "CallInitiationEvent.h"

CallInitiationEvent::CallInitiationEvent(float t, float s, int bid, float p, float d, int no)
	:Event(t, bid, no)
{
	speed = s;
	position = p;
	duration = d;
}

void CallInitiationEvent::handleEvent(Base blist[]){
	Base *base = &blist[baseID];
	int oc = base->getOccupiedChannel(); //occupied channel 
	//cout<<base->toString();
	if(oc<10){
		base->incOccupiedChannel();
		float handoverTS = time + 3600*(DIAMETER-position)/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS)
			if(baseID+1<20)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS, arrivalNo);
			else
				new CallTerminationEvent(handoverTS, baseID, arrivalNo);
		else
			new CallTerminationEvent(terminationTS, baseID, arrivalNo);
	}else
		Event::block++;

}


string CallInitiationEvent::getOutput(Base blist[]){
	stringstream ss;
	//ss<<this->getEventID()<<"\t"<<"Init\t"<<arrivalNo<<"\t"<<time<<"\t"
	//	<<baseID<<"\t"<<speed<<"\t"<<duration<<"\t"<<position<<std::endl;

	ss<<"i"<<"\t"<<time
		<<"\t"<<arrivalNo<<"\t"<<blist[baseID].toString()
		<<endl;

	//ss<<arrivalNo<<"\t"<<time<<endl;
	return ss.str();
}